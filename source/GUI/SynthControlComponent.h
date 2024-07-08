#pragma once

#include "../PluginProcessor.h"
#include "DualKnobComponent.h"
#include "SynthControlKnobRow.h"

class SynthControlComponent : public juce::Component
{
public:
    SynthControlComponent();

    void paint(juce::Graphics& g) override;

private:
    DualKnobComponent knob1;
    SynthControlKnobRow knobRow1;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SynthControlComponent)
};
