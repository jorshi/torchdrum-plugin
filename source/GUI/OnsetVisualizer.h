// Animate the onset signal
#pragma once

#include "../PluginProcessor.h"
#include <juce_gui_basics/juce_gui_basics.h>

class OnsetVisualizer : public juce::Component, juce::Timer
{
public:
    OnsetVisualizer() = delete;
    OnsetVisualizer(TorchDrumProcessor& p);
    ~OnsetVisualizer() override {}

    void paint(juce::Graphics& g) override;
    void resized() override;

    void timerCallback() override;

private:
    TorchDrumProcessor& drumProcessor;
    juce::Path onsetPath;

    int drawResoluationHz = 100;
    int drawSeconds = 2;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OnsetVisualizer)
};
