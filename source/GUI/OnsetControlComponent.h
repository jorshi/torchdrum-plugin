#pragma once

#include "../PluginProcessor.h"
#include <juce_gui_basics/juce_gui_basics.h>

class OnsetControlComponent : public juce::Component
{
public:
    OnsetControlComponent(TorchDrumProcessor& processor);

    void paint(juce::Graphics& g) override;
    void resized() override {}

private:
    TorchDrumProcessor& drumProcessor;
    juce::ColourGradient gradientBackground;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OnsetControlComponent)
};
