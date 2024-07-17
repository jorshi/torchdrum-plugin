#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

struct Parameters
{
    Parameters()
    {
        addParameter(onThreshold);
        addParameter(offThreshold);
        addParameter(waitSamples);
        addParameter(sensitivity);
    }

    void add(juce::AudioProcessor& processor) const
    {
        processor.addParameter(onThreshold);
        processor.addParameter(offThreshold);
        processor.addParameter(waitSamples);
        processor.addParameter(sensitivity);
    }

    void addParameter(juce::RangedAudioParameter* param)
    {
        parameters.push_back(param);
        guiRanges.push_back(juce::NormalisableRange<double>(
            param->getNormalisableRange().start,
            param->getNormalisableRange().end,
            param->getNormalisableRange().interval,
            param->getNormalisableRange().skew,
            param->getNormalisableRange().symmetricSkew));
    }

    // Free parameters -- this is here to support unit testing.
    // Parameters will be owned by the AudioProcessor in the application.
    void freeParameters()
    {
        for (auto* param : parameters)
            delete param;
    }

    // Raw pointers. They will be owned by either the processor or the APVTS (if you use it)
    juce::AudioParameterFloat* onThreshold =
        new juce::AudioParameterFloat({ "onThreshold", 1 },
                                      "Trigger Threshold",
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

    std::vector<juce::RangedAudioParameter*> parameters;
    std::vector<juce::NormalisableRange<double>> guiRanges;
};
