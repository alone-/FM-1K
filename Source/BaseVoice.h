/*
  ==============================================================================

    SynthVoice.h
    Created: 18 Oct 2018 10:52:05pm
    Author:  lain

    Base implementation of the virtual SynthesiserVoice class.
  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class NoteList;
class Oscillator;
class WaveTableCollection;
class Vector;

class BaseVoice : public SynthesiserVoice {
    public:
        BaseVoice();
        BaseVoice(std::vector<Oscillator*>* oscs, float sampleRate);
        
        virtual bool canPlaySound(SynthesiserSound *sound);
        virtual void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition);
        virtual void stopNote(float velocity, bool allowTailOff);
        virtual void pitchWheelMoved(int newPitchWheelValue);
        virtual void controllerMoved(int controllerNumber, int newControllerValue);
        virtual void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples);
    protected: 
        virtual void perSampleUpdate();
        
        std::vector<Oscillator*> *oscs;
        
        float sampleRate;
        float tablePos; 
        float volume;
        float voiceFreq;
};