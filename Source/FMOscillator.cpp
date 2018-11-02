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
#define MAX_MODULATION (32.0)

#define DEFAULT_OFFSET (0)
#define MIN_OFFSET (0.0)
#define MAX_OFFSET (1.0)

#define DEFAULT_LEVEL (0)
#define MIN_LEVEL (0.0)
#define MAX_LEVEL (1.0)

FMOscillator::FMOscillator(juce::AudioProcessor *processor, float sampleRate) : Oscillator(processor, sampleRate) {
    static int fmOscNum;
    
    //audio parameter (DAW-visible) members
    //declare all audio parameters..
    std::stringstream label;
    label << "FM osc" << fmOscNum << "modulation";
    std::stringstream description;
    description << "FM Osc " << fmOscNum << " Modulation";
    
    modulation = new AudioParameterFloat (label.str(), description.str(), MIN_MODULATION, MAX_MODULATION, DEFAULT_MODULATION);
    
    std::stringstream offsetlabel;
    offsetlabel << "FM osc" << fmOscNum << "offset";
    std::stringstream offsetdescription;
    offsetdescription << "FM Osc " << fmOscNum << " Offset";
    
    offset = new AudioParameterFloat (offsetlabel.str(), offsetdescription.str(), MIN_OFFSET, MAX_OFFSET, DEFAULT_OFFSET);
    
    std::stringstream levellabel;
    levellabel << "FM osc" << fmOscNum << "level";
    std::stringstream leveldescription;
    leveldescription << "FM Osc " << fmOscNum << " Level";
    
    level = new AudioParameterFloat (levellabel.str(), leveldescription.str(), MIN_LEVEL, MAX_LEVEL, DEFAULT_LEVEL);
    
    //add parameters to processor...
    if (processor != nullptr) {
        processor->addParameter(modulation);
        processor->addParameter(offset);
        processor->addParameter(level);
    }
    
    fmOscNum++;
}

FMOscillator::~FMOscillator() {
    delete modulation;
}

float FMOscillator::getOffset() {
    return offset->get();
}

float FMOscillator::getModulation() {
    return modulation->get();
}

float FMOscillator::getValue(int tablePos) {
    return Oscillator::getValue(tablePos) * level->get();
}