/*
  ==============================================================================

    VoiceFM.h
    Created: 23 Oct 2018 4:02:36pm
    Author:  lain

    VoiceFM class:
    A voice whose frequency can be modulated by another oscillator.
    
    Parameters:
    
        modulation
        
        scale?
  ==============================================================================
*/

#pragma once

#include "BaseVoice.h"

class FMOscillator;
class Vector;

class FMVoice : public BaseVoice {
    public:
        FMVoice(ADSR *adsr, AudioProcessor *processor, std::vector<Oscillator*> *oscs, std::vector<FMOscillator*> *fmoscs, float sampleRate);
        
    protected:
        virtual void perSampleUpdate();
        
        std::vector<FMOscillator*> *fmoscs;
        float fmTablePos;
};