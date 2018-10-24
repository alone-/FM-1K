/*
  ==============================================================================

    FMOscillator.cpp
    Created: 23 Oct 2018 8:39:39pm
    Author:  lain

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include <sstream>

#include "FMOscillator.h"

#define MIN_MODULATION (0.0)
#define DEFAULT_MODULATION (0.5)
#define MAX_MODULATION (8.0)

FMOscillator::FMOscillator(juce::AudioProcessor *processor, float sampleRate) : Oscillator(processor, sampleRate) {
    static int fmOscNum;
    
    //audio parameter (DAW-visible) members
    //declare all audio parameters..
    std::stringstream label;
    label << "FM osc" << fmOscNum << "modulation";
    std::stringstream description;
    description << "FM Osc " << fmOscNum << " Modulation";
    
    modulation = new AudioParameterFloat (label.str(), description.str(), MIN_MODULATION, MAX_MODULATION, DEFAULT_MODULATION);
    
    //add parameters to processor...
    if (processor != nullptr) {
        processor->addParameter(modulation);
    }
    
    fmOscNum++;
}

FMOscillator::~FMOscillator() {
    delete modulation;
}

float FMOscillator::getModulation() {
    return modulation->get();
}