/*
  ==============================================================================

    Oscillator.h
    Created: 23 Oct 2018 11:55:57am
    Author:  lain

  ==============================================================================
*/

#pragma once

class NoteList;
class WaveTableCollection;

class Oscillator {
    public:
        Oscillator(juce::AudioProcessor *processor, float sampleRate);
        virtual ~Oscillator();
        
        float getValue(int tablePos);
        float getFreq(int midiNote);
    private:
        AudioProcessor *processor;
        NoteList *oscTuning;
        WaveTableCollection *waveTable;
        AudioParameterInt* waveform;
        
        float sampleRate;
};
