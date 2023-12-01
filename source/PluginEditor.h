#pragma once

#include "PluginProcessor.h"

class TorchDrumEditor : public juce::AudioProcessorEditor
{
public:
    explicit TorchDrumEditor(TorchDrumProcessor&);

    // Handle the file chooser callback
    // Send the returned file path to the SynthController
    // to load a new NN model.
    void chooserCallback(const juce::FileChooser& chooser);

private:
    void paint(juce::Graphics&) override;
    void resized() override;

    TorchDrumProcessor& processor;
    juce::GenericAudioProcessorEditor editor { processor };
    juce::TextButton loadModelButton { "Load Model" };
    std::unique_ptr<juce::FileChooser> fileChooser;
};
