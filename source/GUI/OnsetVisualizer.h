// Animate the onset signal
#pragma once

#include "../Parameters.h"
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
    void updateOnsetPath();

    void timerCallback() override;

private:
    TorchDrumProcessor& drumProcessor;
    Parameters& parameters;
    juce::Path onsetPath;

    std::vector<float> drawableSignal;
    size_t writeIndex = 0;
    size_t readIndex = 0;
    size_t drawIndex = 0;

    const int timerHz = 30;
    const int drawResoluationHz = 120;
    const int drawSeconds = 3;

    const float minValue = 0.0f;
    const float maxValue = 60.0f;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OnsetVisualizer)
};
