/*
==============================================================================

SynthParameterBase.h

Base class for handling synth parameters that can be modulated

==============================================================================
*/
#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

struct SynthParameterBase
{
    // You should create a new constructor and add all the parameters there
    SynthParameterBase() = default;
    ~SynthParameterBase() = default;

    void add(juce::AudioProcessor& processor) const
    {
        for (auto* param : parameters)
            processor.addParameter(param);
    }

    void addParameter(juce::RangedAudioParameter* param)
    {
        parameters.push_back(param);

        // Create a dummy callback for this parameter
        callbacks.push_back([](float) {});
    }

    void updateAllParameters()
    {
        for (int i = 0; i < parameters.size(); ++i)
        {
            auto* param = parameters[i];
            auto& callback = callbacks[i];
            callback(param->convertFrom0to1(param->getValue()));
        }
    }

    void addCallback(int index, std::function<void(float)> callback)
    {
        jassert(index < callbacks.size());
        callbacks[index] = callback;
    }

    // Free parameters -- this is here to support unit testing.
    // Parameters will be owned by the AudioProcessor in the application.
    void freeParameters()
    {
        for (auto* param : parameters)
            delete param;
    }

    std::vector<juce::RangedAudioParameter*> parameters;
    std::vector<std::function<void(float)>> callbacks;
};