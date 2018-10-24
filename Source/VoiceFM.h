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

class FMVoice : public BaseVoice {
    public:
        FMVoice(AudioProcessor *processor, Oscillator **oscs, FMOscillator *fmOsc, int numOscs, float sampleRate);
        
    protected:
        virtual void perSampleUpdate();
        
        FMOscillator *fmOsc;
        float fmTablePos;
};