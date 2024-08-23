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
        guiCallbacks.push_back([](float) {});

        // Create a GUI range for this parameter
        guiRanges.push_back(juce::NormalisableRange<double>(
            param->getNormalisableRange().start,
            param->getNormalisableRange().end,
            param->getNormalisableRange().interval,
            param->getNormalisableRange().skew,
            param->getNormalisableRange().symmetricSkew));
    }

    void updateAllParameters()
    {
        for (size_t i = 0; i < parameters.size(); ++i)
        {
            auto* param = parameters[i];
            auto& callback = callbacks[i];
            callback(param->convertFrom0to1(param->getValue()));
        }
    }

    void updateAllParametersWithModulation(const std::vector<double>& modulation,
                                           float sensitivity = 1.0f)
    {
        jassert(modulation.size() == parameters.size());
        for (size_t i = 0; i < parameters.size(); ++i)
        {
            auto* param = parameters[i];
            auto& callback = callbacks[i];
            auto& guiCallback = guiCallbacks[i];

            float modAmount = (float) modulation[i] * sensitivity;
            float value = juce::jlimit(0.0f, 1.0f, param->getValue() + modAmount);

            callback(param->convertFrom0to1(value));
            guiCallback(value);
        }
    }

    void addCallback(size_t index, std::function<void(float)> callback)
    {
        jassert(index < callbacks.size());
        callbacks[index] = callback;
    }

    void addGUICallback(size_t index, std::function<void(float)> callback)
    {
        jassert(index < guiCallbacks.size());
        guiCallbacks[index] = callback;
    }

    void removeGUICallback(size_t index)
    {
        jassert(index < guiCallbacks.size());
        guiCallbacks[index] = [](float) {};
    }

    void removeAllGUICallbacks()
    {
        for (auto i = 0; i < guiCallbacks.size(); ++i)
            removeGUICallback(i);
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
    std::vector<std::function<void(float)>> guiCallbacks;
    std::vector<juce::NormalisableRange<double>> guiRanges;
};
