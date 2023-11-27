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
        addParameter(tonalDecay);
        addParameter(tonalTuning);
    }

    juce::AudioParameterFloat* tonalDecay =
        new juce::AudioParameterFloat({ "tonal_decay", 1 }, "Tonal Decay", 0.f, 1.f, 0.62f);

    juce::AudioParameterFloat* tonalTuning =
        new juce::AudioParameterFloat({ "tonal_tuning", 1 }, "Tonal Tuning", 0.f, 1.f, 0.5f);
};
