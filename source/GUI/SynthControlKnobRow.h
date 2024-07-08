#pragma once

#include "../PluginProcessor.h"
#include "DualKnobComponent.h"

class SynthControlKnobRow : public juce::Component
{
public:
    SynthControlKnobRow();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void setNumKnobs(int newValue);

private:
    int numKnobs = 0;
    std::vector<juce::Rectangle<int>> knobBounds;
    std::vector<std::unique_ptr<DualKnobComponent>> knobs;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SynthControlKnobRow)
};
