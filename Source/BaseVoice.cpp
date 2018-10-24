/*
  ==============================================================================

    SynthVoice.cpp
    Created: 18 Oct 2018 10:52:05pm
    Author:  lain

  ==============================================================================
*/

#include <vector>
#include "BaseVoice.h"
#include "Oscillator.h"

#define DEFAULT_SAMPLE_RATE (44100)

BaseVoice::BaseVoice() : BaseVoice(nullptr, DEFAULT_SAMPLE_RATE) { }

BaseVoice::BaseVoice(std::vector<Oscillator*> *oscs, float sampleRate) : SynthesiserVoice() {
    this->oscs = oscs;
    this->sampleRate = sampleRate;
    
    tablePos = 0;
    voiceFreq = 0;
    volume = 0;
}

bool BaseVoice::canPlaySound(SynthesiserSound *sound) {
    //We aren't going to worry about casting and simply assume that as long as
    //the sound past was not null, that we can play it.
    return (sound != nullptr);
}

void BaseVoice::startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) {
    //this basic implementation just uses the tuning of the first oscillator, since generally
    //all oscillators in a synth use the same scale. If you wish to have different oscillators use
    //different scales, it is up to you to determine which to use (or average the frequencies).
    voiceFreq = oscs->at(0)->getFreq(midiNoteNumber);
    tablePos = 0;
    volume = 1.0;
}

void BaseVoice::stopNote(float velocity, bool allowTailOff) {
    clearCurrentNote();
    volume = 0;
}

void BaseVoice::pitchWheelMoved(int newPitchWheelValue) {
}

void BaseVoice::controllerMoved(int controllerNumber, int newControllerValue) {
}

void BaseVoice::renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples) {
    float val;
    
    for (int sample = 0; sample < numSamples; ++sample) {
        val = 0;
        
        //sum samples from each oscillator
        for (int osc = 0; osc < oscs->size(); osc++) {
            val += oscs->at(osc)->getValue((int)tablePos);
        } 
            
        //divide by the number of oscs so no values exceed the min or max (-1, 1)
        val /= oscs->size();
        
        for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
            outputBuffer.addSample(channel, startSample, val * volume);
        }
        
        perSampleUpdate();
        
        ++startSample;
    }
}

/* perSampleUpdate

    Perform any operations that much be done after calculating every sample,
    such as updating the table position.
*/

void BaseVoice::perSampleUpdate() {
    tablePos += voiceFreq;
            
    //this relies on the fact that our tables are made to correspond to 1hz waves
    //and so are sized equal to the sample rate. could store the max table pos in
    //the class itself to avoid this potential coupling issue
    if (tablePos >= sampleRate)
        tablePos -= sampleRate;  //as long as the frequency is not > sampleRate this will work properly        
    if (tablePos < 0)
        tablePos = 0;
}