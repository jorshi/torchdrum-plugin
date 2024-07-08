#pragma once

#include "../PluginProcessor.h"
#include "SynthControlKnobRow.h"

class SynthControlComponent : public juce::Component
{
public:
    SynthControlComponent();

    void paint(juce::Graphics& g) override;

private:
    SynthControlKnobRow knobRow1;
    SynthControlKnobRow knobRow2;
    SynthControlKnobRow knobRow3;
    SynthControlKnobRow knobRow4;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SynthControlComponent)
};
