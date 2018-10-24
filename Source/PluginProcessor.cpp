/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "VoiceFM.h"
#include "FMOscillator.h"

#define OSCILLATORS (1)
#define VOICES (8)

//==============================================================================
Fm1kAudioProcessor::Fm1kAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    synth.clearVoices();

    Oscillator **oscs = new Oscillator*[OSCILLATORS];
    FMOscillator *fmosc = new FMOscillator(this, 44100);
    
    for (int i = 0; i < OSCILLATORS; i++ ) {
        oscs[i] = new Oscillator(this, 44100);
    }
    
    
    for (int i = 0; i < VOICES; i++) {
        synth.addVoice(new FMVoice(this, oscs, fmosc, OSCILLATORS, 44100));
    }
    
    synth.clearSounds();
    synth.addSound(new BaseSound());
}

Fm1kAudioProcessor::~Fm1kAudioProcessor()
{
}

//==============================================================================
const String Fm1kAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Fm1kAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Fm1kAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Fm1kAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Fm1kAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Fm1kAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Fm1kAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Fm1kAudioProcessor::setCurrentProgram (int index)
{
}

const String Fm1kAudioProcessor::getProgramName (int index)
{
    return {};
}

void Fm1kAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Fm1kAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
}

void Fm1kAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Fm1kAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Fm1kAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    buffer.clear();
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool Fm1kAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Fm1kAudioProcessor::createEditor()
{
    return new Fm1kAudioProcessorEditor (*this);
}

//==============================================================================
void Fm1kAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Fm1kAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Fm1kAudioProcessor();
}
