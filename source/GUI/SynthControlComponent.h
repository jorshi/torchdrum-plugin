#pragma once

#include "../PluginProcessor.h"

class SynthControlComponent : public juce::Component
{
public:
    SynthControlComponent();

    void paint(juce::Graphics& g) override;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SynthControlComponent)
};
