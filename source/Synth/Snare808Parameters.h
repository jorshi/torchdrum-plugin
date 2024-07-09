/*
==============================================================================

DrumSynthParameters.h

Class to hold the parameters for the drum synth

==============================================================================
*/

#pragma once

#include "SynthParameterBase.h"

struct Snare808Parameters : public SynthParameterBase
{
    Snare808Parameters()
    {
        addParameter(osc1Freq);
        addParameter(osc1Mod);
        addParameter(osc2Freq);
        addParameter(osc2Mod);
        addParameter(freqEnvDecay);
        addParameter(osc1Decay);
        addParameter(osc2Decay);
        addParameter(noiseEnvDecay);
        addParameter(noiseFilterFreq);
        addParameter(noiseFilterQ);
        addParameter(osc1Gain);
        addParameter(osc2Gain);
        addParameter(noiseGain);
        addParameter(tanhGain);
    }

    juce::AudioParameterFloat* osc1Freq =
        new juce::AudioParameterFloat({ "osc1_freq", 1 }, "Freq", 20.f, 2000.f, 180.f);

    juce::AudioParameterFloat* osc1Mod =
        new juce::AudioParameterFloat({ "osc1_mod", 1 }, "Mod", -1.0f, 2.f, 0.4f);

    juce::AudioParameterFloat* osc2Freq =
        new juce::AudioParameterFloat({ "osc2_freq", 1 }, "Freq", 20.f, 2000.f, 240.f);

    juce::AudioParameterFloat* osc2Mod =
        new juce::AudioParameterFloat({ "osc2_mod", 1 }, "Mod", -1.0f, 2.f, 0.3f);

    juce::AudioParameterFloat* freqEnvDecay =
        new juce::AudioParameterFloat({ "freq_env_decay", 1 },
                                      "Mod Decay",
                                      10.f,
                                      2000.f,
                                      50.f);

    juce::AudioParameterFloat* osc1Decay =
        new juce::AudioParameterFloat({ "osc1_decay", 1 },
                                      "Decay",
                                      10.f,
                                      2000.f,
                                      200.f);

    juce::AudioParameterFloat* osc2Decay =
        new juce::AudioParameterFloat({ "osc2_decay", 1 },
                                      "Decay",
                                      10.f,
                                      2000.f,
                                      150.f);

    juce::AudioParameterFloat* noiseEnvDecay =
        new juce::AudioParameterFloat({ "noise_env_decay", 1 },
                                      "Decay",
                                      10.f,
                                      2000.f,
                                      200.f);

    juce::AudioParameterFloat* noiseFilterFreq =
        new juce::AudioParameterFloat({ "noise_filter_freq", 1 },
                                      "Freq",
                                      20.f,
                                      24000.f,
                                      2500.f);

    juce::AudioParameterFloat* noiseFilterQ =
        new juce::AudioParameterFloat({ "noise_filter_q", 1 }, "Res", 0.5f, 10.f, 2.f);

    juce::AudioParameterFloat* osc1Gain =
        new juce::AudioParameterFloat({ "osc1_gain", 1 }, "Gain", -60.0f, 6.0f, -6.f);

    juce::AudioParameterFloat* osc2Gain =
        new juce::AudioParameterFloat({ "osc2_gain", 1 }, "Gain", -60.0f, 6.0f, -12.f);

    juce::AudioParameterFloat* noiseGain =
        new juce::AudioParameterFloat({ "noise_gain", 1 }, "Gain", -60.0f, 6.0f, -4.f);

    juce::AudioParameterFloat* tanhGain =
        new juce::AudioParameterFloat({ "tanh_gain", 1 },
                                      "Waveshape",
                                      -24.0f,
                                      24.0f,
                                      -12.f);
};
