#pragma once

#include "../PluginProcessor.h"
#include "DualKnobComponent.h"
#include <juce_gui_basics/juce_gui_basics.h>

class GlobalControlComponent : public juce::Component
{
public:
    GlobalControlComponent(TorchDrumProcessor& processor);

    void paint([[maybe_unused]] juce::Graphics& g) override {}
    void resized() override;

private:
    TorchDrumProcessor& drumProcessor;

    std::unique_ptr<DualKnobComponent> dryWetKnob;
    std::unique_ptr<DualKnobComponent> neuralKnob;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GlobalControlComponent)
};
