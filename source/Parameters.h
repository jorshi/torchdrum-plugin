#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

class Parameters
{
public:
    Parameters()
    {
        parameters.push_back(sensitivity);
    }

    void add(juce::AudioProcessor& processor) const
    {
        processor.addParameter(sensitivity);
    }

    // Free parameters -- this is here to support unit testing.
    // Parameters will be owned by the AudioProcessor in the application.
    void freeParameters()
    {
        for (auto* param : parameters)
            delete param;
    }

    //Raw pointers. They will be owned by either the processor or the APVTS (if you use it)
    juce::AudioParameterFloat* sensitivity =
        new juce::AudioParameterFloat({ "sensitivity", 1 }, "Sensitivity", 0.f, 4.f, 1.0f);

private:
    std::vector<juce::RangedAudioParameter*> parameters;
};
