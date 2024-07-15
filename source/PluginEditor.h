#pragma once

#include "BinaryData.h"
#include "GUI/ButtonControlComponent.h"
#include "GUI/GlobalControlComponent.h"
#include "GUI/OnsetControlComponent.h"
#include "GUI/SynthControlComponent.h"
#include "GUI/VisualizerComponent.h"
#include "PluginProcessor.h"

class TorchDrumEditor : public juce::AudioProcessorEditor, juce::ActionListener
{
public:
    explicit TorchDrumEditor(TorchDrumProcessor&);
    ~TorchDrumEditor() override;

    // Handle the file chooser callback
    // Send the returned file path to the SynthController
    // to load a new NN model.
    void chooserCallback(const juce::FileChooser& chooser);

    // TODO: Is this specific for Mac OS X?
    const juce::String SupportFolder = "Application Support";
    const juce::String AppFolder = "TorchDrum";
    const juce::String PresetFolder = "Presets";
    const juce::String FactoryFolder = "Factory";

    // Callback for action listener
    void actionListenerCallback(const juce::String& message) override;

private:
    void paint(juce::Graphics&) override;
    void resized() override;

    juce::File getPresetFolder();

    TorchDrumProcessor& drumProcessor;
    std::unique_ptr<juce::FileChooser> fileChooser;

    // Background image
    juce::Image backgroundImage;

    // GUI Components
    ButtonControlComponent buttonControlComponent;
    GlobalControlComponent globalControlComponent;
    OnsetControlComponent onsetControlComponent;
    SynthControlComponent synthControlComponent;
    VisualizerComponent visualizerComponent;
};
