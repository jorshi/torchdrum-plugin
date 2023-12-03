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

    // TODO: Is this specific for Mac OS X?
    const juce::String SupportFolder = "Application Support";
    const juce::String AppFolder = "TorchDrum";
    const juce::String PresetFolder = "Presets";
    const juce::String FactoryFolder = "Factory";

private:
    void paint(juce::Graphics&) override;
    void resized() override;

    juce::File getPresetFolder();

    TorchDrumProcessor& processor;
    juce::GenericAudioProcessorEditor editor { processor };
    juce::TextButton loadModelButton { "Load Model" };
    std::unique_ptr<juce::FileChooser> fileChooser;
};
