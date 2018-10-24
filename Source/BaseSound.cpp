/*
  ==============================================================================

    SynthSound.cpp
    Created: 18 Oct 2018 10:51:58pm
    Author:  lain

  ==============================================================================
*/

#include "BaseSound.h"

bool BaseSound::appliesToNote(int note) {
    return true;
}

bool BaseSound::appliesToChannel(int channel) {
    return true;
}