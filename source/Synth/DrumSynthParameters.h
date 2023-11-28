/*
==============================================================================

DrumSynthParameters.h

Class to hold the parameters for the drum synth

==============================================================================
*/

#pragma once

#include "SynthParameterBase.h"

struct DrumSynthParameters : public SynthParameterBase
{
    DrumSynthParameters()
    {
        addParameter(ampEnvDecay);
        addParameter(freqEnvDecay);
        addParameter(oscFreq);
        addParameter(oscMod);
        addParameter(tanhGain);
        addParameter(outGain);
        addParameter(noiseEnvDecay);
        addParameter(noiseGain);
    }

    juce::AudioParameterFloat* ampEnvDecay =
        new juce::AudioParameterFloat({ "amp_env_decay", 1 }, "Amp Env Decay", 10.f, 2000.f, 500.f);

    juce::AudioParameterFloat* freqEnvDecay =
        new juce::AudioParameterFloat({ "freq_env_decay", 1 }, "Freq Env Decay", 10.f, 2000.f, 500.f);

    juce::AudioParameterFloat* oscFreq =
        new juce::AudioParameterFloat({ "osc_freq", 1 }, "Osc Freq", 20.f, 2000.f, 100.f);

    juce::AudioParameterFloat* oscMod =
        new juce::AudioParameterFloat({ "osc_mod", 1 }, "Osc Mod", -1.0f, 2.f, 0.f);

    juce::AudioParameterFloat* tanhGain =
        new juce::AudioParameterFloat({ "tanh_gain", 1 }, "Tanh Gain", -24.0f, 24.0f, 0.f);

    juce::AudioParameterFloat* outGain =
        new juce::AudioParameterFloat({ "out_gain", 1 }, "Out Gain", -60.0f, 6.0f, 0.f);

    juce::AudioParameterFloat* noiseEnvDecay =
        new juce::AudioParameterFloat({ "noise_env_decay", 1 }, "Noise Env Decay", 10.f, 2000.f, 500.f);

    juce::AudioParameterFloat* noiseGain =
        new juce::AudioParameterFloat({ "noise_gain", 1 }, "Noise Gain", -60.0f, 6.0f, 0.f);
};
