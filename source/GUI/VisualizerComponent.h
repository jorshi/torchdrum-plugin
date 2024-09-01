#pragma once

#include "../PluginProcessor.h"
#include "FeatureVisualizer.h"
#include "OnsetVisualizer.h"
#include <juce_gui_basics/juce_gui_basics.h>

class VisualizerComponent : public juce::Component
{
public:
    VisualizerComponent(TorchDrumProcessor& processor);

    void paint(juce::Graphics& g) override;

    void resized() override;

private:
    TorchDrumProcessor& drumProcessor;

    FeatureVisualizer featureVisualizer { drumProcessor };
    OnsetVisualizer onsetVisualizer;

    juce::TextButton resetButton;
    juce::ColourGradient gradientBackground;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VisualizerComponent)
};
