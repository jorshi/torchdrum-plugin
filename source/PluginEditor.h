#pragma once

#include "PluginProcessor.h"

class TorchDrumEditor : public juce::AudioProcessorEditor
{
public:
    explicit TorchDrumEditor(TorchDrumProcessor&);

private:
    void paint(juce::Graphics&) override;
    void resized() override;

    juce::GenericAudioProcessorEditor editor { processor };
};
