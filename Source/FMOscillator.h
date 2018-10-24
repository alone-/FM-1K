/*
  ==============================================================================

    FMOscillator.h
    Created: 23 Oct 2018 8:39:39pm
    Author:  lain

  ==============================================================================
*/

#pragma once

#include "Oscillator.h"

class FMOscillator : public Oscillator {
    public:
        FMOscillator(juce::AudioProcessor *processor, float sampleRate);
        virtual ~FMOscillator();
        
        float getModulation();
    private:
        AudioParameterFloat* modulation;
};