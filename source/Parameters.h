#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

struct Parameters
{
    void add(juce::AudioProcessor& processor) const
    {
        processor.addParameter(sensitivity);
    }

    //Raw pointers. They will be owned by either the processor or the APVTS (if you use it)
    juce::AudioParameterFloat* sensitivity =
        new juce::AudioParameterFloat({ "sensitivity", 1 }, "Sensitivity", 0.f, 1.f, 0.5f);
};
