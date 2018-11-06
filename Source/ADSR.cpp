/*
  ==============================================================================

    ADSR.cpp
    Created: 3 Nov 2018 12:39:54pm
    Author:  lain

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "ADSR.h"

#define DEFAULT_ATTACK (0)
#define DEFAULT_DECAY (0)
#define DEFAULT_SUSTAIN (1.0)
#define DEFAULT_RELEASE (0.0)

#define MIN_ADSR_TIME (0.1)
#define MAX_ADSR_TIME (20)

ADSRParams::ADSRParams(AudioProcessor *processor, float sampleRate) {
    //adsr audio parameters.......
    //adr are displayed to the user in seconds, but attackamt, decayamnt and releaseamnt
    //refer to how much the level should increase by per sample
    attack = new AudioParameterFloat ("attack", "Attack", MIN_ADSR_TIME, MAX_ADSR_TIME, DEFAULT_ATTACK);
    decay = new AudioParameterFloat ("decay", "Decay", MIN_ADSR_TIME, MAX_ADSR_TIME, DEFAULT_ATTACK);
    sustain = new AudioParameterFloat ("sustain", "Sustain", 0.0, 1.0, 1.0);
    release = new AudioParameterFloat ("release", "Release", MIN_ADSR_TIME, MAX_ADSR_TIME, DEFAULT_ATTACK);
    
    //add parameters to processor...
    if (processor != nullptr) {
        processor->addParameter(attack);
        processor->addParameter(decay);
        processor->addParameter(sustain);
        processor->addParameter(release);
    }
    
    setSampleRate(sampleRate);
}

void ADSRParams::setSampleRate(float sampleRate) {
    this->sampleRate = sampleRate;
    
    //whenever sample rate changes, the adsr parameters
    //must be updated!
    updateParams();
}

void ADSRParams::updateParams() {
    //attack/decay/release amounts per sample
    //note: if the min ADSR time is set too low then you can encounter
    //errors calculating the attackamt/decayamt/releaseamt.
    //if ADSR time is set to 0 you will definitely encounter errors.
    attackamt = 1.0f / (sampleRate * attack->get());
    decayamt = 1.0f / ((sampleRate * (1.0 - sustain->get())) * decay->get());
    releaseamt = 1.0f / (sampleRate * release->get());
}

float ADSRParams::sampleattack() {
    return attackamt;
}

float ADSRParams::sampledecay() {
    return decayamt;
}

float ADSRParams::samplerelease() {
    return releaseamt;
}

float ADSRParams::getSustain() {
    return sustain->get();
}

ADSR::ADSR(ADSRParams* params) {
    this->params = params;
    state = ADSR_RELEASE;
    curlevel = 0.0;
}

void ADSR::start() {
    //update params incase they were changed, alternatively this could be on value change for each param...
    params->updateParams();
    //set state
    state = ADSR_ATTACK;
    //whenever we start an attack we should re-calculate the attack amount
    //based on the current level (as the voice may have been playing another note)
    attack = (1-curlevel) * params->sampleattack();
}

void ADSR::stop() {
    state = ADSR_RELEASE;
    //whenever we start a release we should re-calculate the release amount
    //based on the current level (as the attack may not have been finished)
    release = curlevel * params->samplerelease();
}

void ADSR::update() {
    switch(state) {
        case (ADSR_ATTACK):
            if (curlevel < 1.0) {
                curlevel += attack;
            }
            else {
                curlevel = 1.0;
                state = ADSR_DECAY;
            }
            break;
        case (ADSR_DECAY):
            if (curlevel > params->getSustain()) {
                curlevel -= params->sampledecay();
            }
            else {
                curlevel = params->getSustain();
                state = ADSR_SUSTAIN;
            }
            break;
        case (ADSR_RELEASE):
            if (curlevel > 0) {
                curlevel -= release;
            }
            else {
                curlevel = 0;
            }
            break;
    }
}

float ADSR::level() {
    return curlevel;
}
