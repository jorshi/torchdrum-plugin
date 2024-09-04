#pragma once

#include "../PluginProcessor.h"
#include "SynthControlKnobRow.h"

class SynthControlComponent : public juce::Component, juce::ActionListener
{
public:
    SynthControlComponent(TorchDrumProcessor& processor);
    ~SynthControlComponent() override;

    void paint([[maybe_unused]] juce::Graphics& g) override {}
    void resized() override;

    // Callback for action listener
    void actionListenerCallback(const juce::String& message) override;

private:
    void connectParameters(std::vector<std::vector<int>>& connections,
                           std::vector<std::string>& labels);

    std::vector<std::unique_ptr<SynthControlKnobRow>> knobRows;
    SynthControlKnobRow knobRow1;
    SynthControlKnobRow knobRow2;
    SynthControlKnobRow knobRow3;
    SynthControlKnobRow knobRow4;

    TorchDrumProcessor& drumProcessor;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SynthControlComponent)
};
