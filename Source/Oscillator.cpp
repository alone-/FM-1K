/*
  ==============================================================================

    Oscillator.cpp
    Created: 23 Oct 2018 11:55:57am
    Author:  lain

  ==============================================================================
*/
#include "../JuceLibraryCode/JuceHeader.h"

#include <sstream>

#include "Oscillator.h"
#include "Notes.h"
#include "WaveTables.h"


#define DEFAULT_SAMPLE_RATE (44100)
#define DEFAULT_WAVEFORM (W_TRI)

Oscillator::Oscillator(AudioProcessor *processor, float sampleRate) {
    //keep a counter of which osc is which for audio parameter identification
    static int oscNum = 0;
    
    this->processor = processor;
    oscTuning = new NoteList();
    waveTable = new WaveTableCollection(sampleRate);
    this->sampleRate = sampleRate;

    //audio parameter (DAW-visible) members
    //declare all audio parameters..
    std::stringstream label;
    label << "osc" << oscNum << "wave";
    std::stringstream description;
    description << "Oscillator " << oscNum << " Waveform";
    
    waveform = new AudioParameterInt (label.str(), description.str(), 0, NUM_WAVEFORMS - 1, 0);
    
    //add parameters to processor...
    if (processor != nullptr) {
        processor->addParameter(waveform);
    }
    
    oscNum++;
}

Oscillator::~Oscillator() {
    delete oscTuning;
    delete waveTable;
}

float Oscillator::getFreq(int midiNote) {
    return oscTuning->getFreq(midiNote);
}

float Oscillator::getValue(int tablePos) {
    return waveTable->getTableValue((wave_t)waveform->get(), tablePos);
}