#pragma once

#include "../PluginProcessor.h"
#include "ButtonLookAndFeel.h"
#include <juce_gui_basics/juce_gui_basics.h>

class ButtonControlComponent : public juce::Component
{
public:
    ButtonControlComponent(TorchDrumProcessor& processor);

    void paint([[maybe_unused]] juce::Graphics& g) override {}
    void resized() override;

    juce::File getPresetFolder();

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
    TorchDrumProcessor& drumProcessor;
    std::unique_ptr<juce::FileChooser> fileChooser;

    juce::TextButton loadButton;
    juce::TextButton saveButton;
    juce::TextButton fineTuneButton;
    juce::TextButton aboutButton;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ButtonControlComponent)
};
