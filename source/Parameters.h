#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

class Parameters
{
public:
    Parameters()
    {
        parameters.push_back(onThreshold);
        parameters.push_back(offThreshold);
        parameters.push_back(waitSamples);
        parameters.push_back(sensitivity);
        parameters.push_back(drywet);
    }

    void add(juce::AudioProcessor& processor) const
    {
        processor.addParameter(onThreshold);
        processor.addParameter(offThreshold);
        processor.addParameter(waitSamples);
        processor.addParameter(sensitivity);
        processor.addParameter(drywet);
    }

    // Free parameters -- this is here to support unit testing.
    // Parameters will be owned by the AudioProcessor in the application.
    void freeParameters()
    {
        for (auto* param : parameters)
            delete param;
    }

    // Raw pointers.
    // They will be owned by the AudioProcessor in the application.
    juce::AudioParameterFloat* onThreshold =
        new juce::AudioParameterFloat({ "onThreshold", 1 },
                                      "On Threshold",
                                      0.5f,
                                      32.f,
                                      16.0f);
    juce::AudioParameterFloat* offThreshold =
        new juce::AudioParameterFloat({ "offThreshold", 1 },
                                      "Off Threshold",
                                      0.0f,
                                      32.f,
                                      4.66f);
    juce::AudioParameterInt* waitSamples =
        new juce::AudioParameterInt({ "waitSamples", 1 },
                                    "Wait Samples",
                                    0,
                                    5000,
                                    1000);
    juce::AudioParameterFloat* sensitivity =
        new juce::AudioParameterFloat({ "sensitivity", 1 },
                                      "Mapping Sensitivity",
                                      0.f,
                                      4.f,
                                      1.0f);
    juce::AudioParameterFloat* drywet =
        new juce::AudioParameterFloat({ "drywet", 1 }, "Dry/Wet", 0.0f, 1.0f, 1.0f);

private:
    std::vector<juce::RangedAudioParameter*> parameters;
};
