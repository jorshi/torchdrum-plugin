#pragma once

#include "../PluginProcessor.h"
#include "SynthControlKnobRow.h"

class SynthControlComponent : public juce::Component
{
public:
    SynthControlComponent(TorchDrumProcessor& processor);

    void paint([[maybe_unused]] juce::Graphics& g) override {}
    void resized() override;

private:
    SynthControlKnobRow knobRow1;
    SynthControlKnobRow knobRow2;
    SynthControlKnobRow knobRow3;
    SynthControlKnobRow knobRow4;

    TorchDrumProcessor& drumProcessor;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SynthControlComponent)
};
