/*
  ==============================================================================

    SynthSound.h
    Created: 18 Oct 2018 10:51:58pm
    Author:  lain

    Minimal implementation of the virtual SynthesizerSound class, which
    accepts any note on any channel.
  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class BaseSound : public SynthesiserSound
{
    public:
        //does the sound play when this midi note is pressed?
        virtual bool appliesToNote( int note );
        //or on this channel?
        virtual bool appliesToChannel( int channel );
};