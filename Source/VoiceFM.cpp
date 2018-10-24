/*
  ==============================================================================

    VoiceFM.cpp
    Created: 23 Oct 2018 4:02:36pm
    Author:  lain

  ==============================================================================
*/

#include "VoiceFM.h"

#include "FMOscillator.h"

FMVoice::FMVoice(AudioProcessor *processor, Oscillator **oscs, FMOscillator *fmOsc, int numOscs, float sampleRate) 
    :BaseVoice(oscs, numOscs, sampleRate) {
    fmTablePos = 0;
    this->fmOsc = fmOsc;
}

void FMVoice::perSampleUpdate() {
   // float fmFreq = (voiceFreq + (voiceFreq * (modulation->get() * fmOsc->getValue((int)fmTablePos)))) / 2;
    float fmFreq = voiceFreq + ((voiceFreq * (fmOsc->getModulation() * fmOsc->getValue((int)fmTablePos))) * fmOsc->getOffset());
    tablePos += fmFreq;
    fmTablePos += voiceFreq;
            
    //this relies on the fact that our tables are made to correspond to 1hz waves
    //and so are sized equal to the sample rate. could store the max table pos in
    //the class itself to avoid this potential coupling issue
    if (tablePos >= sampleRate)
        tablePos -= sampleRate;  //as long as the frequency is not > sampleRate this will work properly        
    if (tablePos < 0)
        tablePos = 0;
        
    if (fmTablePos >= sampleRate)
        fmTablePos -= sampleRate;
    if (fmTablePos < 0)
        fmTablePos = 0;
}