#pragma once

#include "../PluginProcessor.h"
#include "DualKnobComponent.h"
#include <juce_gui_basics/juce_gui_basics.h>

class OnsetControlComponent : public juce::Component
{
public:
    OnsetControlComponent(TorchDrumProcessor& processor);

    void paint([[maybe_unused]] juce::Graphics& g) override {};
    void resized() override;

private:
    TorchDrumProcessor& drumProcessor;

    // Knobs
    std::unique_ptr<DualKnobComponent> triggerThresholdKnob;
    std::unique_ptr<DualKnobComponent> retriggerThresholdKnob;
    std::unique_ptr<DualKnobComponent> holdTimeKnob;

    juce::ColourGradient gradientBackground;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OnsetControlComponent)
};
