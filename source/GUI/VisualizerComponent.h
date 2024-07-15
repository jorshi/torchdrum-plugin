#pragma once

#include "../PluginProcessor.h"
#include <juce_gui_basics/juce_gui_basics.h>

class VisualizerComponent : public juce::Component
{
public:
    VisualizerComponent(TorchDrumProcessor& processor);

    void paint(juce::Graphics& g) override;

private:
    TorchDrumProcessor& drumProcessor;

    juce::ColourGradient gradientBackground;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VisualizerComponent)
};
