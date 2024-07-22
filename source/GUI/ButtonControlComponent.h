#pragma once

#include "../PluginProcessor.h"
#include "ButtonLookAndFeel.h"
#include <juce_gui_basics/juce_gui_basics.h>

class ButtonControlComponent : public juce::Component
{
public:
    ButtonControlComponent(TorchDrumProcessor& processor);

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    TorchDrumProcessor& drumProcessor;
    juce::ColourGradient gradientBackground;

    juce::TextButton loadButton;
    juce::TextButton saveButton;
    juce::TextButton fineTuneButton;
    juce::TextButton aboutButton;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ButtonControlComponent)
};
