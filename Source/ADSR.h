/*
  ==============================================================================

    ADSR.h
    Created: 3 Nov 2018 12:39:54pm
    Author:  lain

    ADSR Class:
        Contains an ADSR state + parameters for
        a voice or group of voices (synthesizer).
        
    How it works:
        Changes state based on key input (press or release) and 
        current time/level
        
        state changes:
            on key press:
                state becomes attack
            on key release:
                state becomes release
                
            on update:
                attack:
                    level >= 1.0 -> decay
                decay:
                    level <= sustain -> sustain
                sustain:
                    sustain->sustain, always
                release:
                    release->release, always
                    level < 0 -> level = 0
        
  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

typedef enum ADSR_STATE { ADSR_ATTACK, ADSR_DECAY, ADSR_SUSTAIN, ADSR_RELEASE } adsr_state;

//this is a separate class since while each voice may need its own
//"active" adsr which update separately, they will share the same
//master ADSR parameters in most uses.
class ADSRParams {
    public:
        ADSRParams(AudioProcessor *processor, float sampleRate);
        
        void setSampleRate(float sampleRate);
        void updateParams();
        
        float sampleattack();
        float sampledecay();
        float getSustain();
        float samplerelease();
    private:
        AudioParameterFloat* attack;
        AudioParameterFloat* decay;
        AudioParameterFloat* sustain;
        AudioParameterFloat* release;
        
        float sampleRate;
        float attackamt;   //level delta per attacking sample
        float decayamt;    //level delta per decay sample
        float releaseamt;  //level delta per release sample
};

class ADSR {
    public:
        ADSR(ADSRParams* params);
        
        void update();
        void start();   //start, as in a key was pressed
        void stop();    //stop, as in a key was released
        float level();
        
    private:
        ADSRParams* params;
        
        float curlevel;
        
        adsr_state state;
        
        //attack and release variables are kept because they may
        //change if notes are released or pressed before another is
        //totally finished
        float attack;
        float release;
};