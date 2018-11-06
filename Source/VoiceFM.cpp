/*
  ==============================================================================

    VoiceFM.cpp
    Created: 23 Oct 2018 4:02:36pm
    Author:  lain

  ==============================================================================
*/

#include "VoiceFM.h"

#include "FMOscillator.h"

FMVoice::FMVoice(ADSR *adsr, AudioProcessor *processor, std::vector<Oscillator*> *oscs, std::vector<FMOscillator*> *fmoscs, float sampleRate) 
    :BaseVoice(adsr, oscs, sampleRate) {
    fmTablePos = 0;
    this->fmoscs = fmoscs;
}

void FMVoice::perSampleUpdate() {
    float fmFreq = 0;
    
    for (int i = 0; i < fmoscs->size(); i++) {
        //this calculation works as follows:
        //the frequency of each oscillator is the sum of three parts
        //1. voiceFreq; the base oscillator frequency
        //2. a modulation of the voiceFreq which modulated at the frequency of the current FM oscillator
        //3. a frequency offset from the previous calculated FM sample
        fmFreq += voiceFreq + ((voiceFreq * (fmoscs->at(i)->getModulation() * fmoscs->at(i)->getValue((int)fmTablePos))));
        fmFreq += fmFreq * fmoscs->at(i)->getOffset();
    }
    
    fmFreq /= fmoscs->size();
    
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