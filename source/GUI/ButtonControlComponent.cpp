#include "ButtonControlComponent.h"
#include "TorchDrumStyle.h"

ButtonControlComponent::ButtonControlComponent(TorchDrumProcessor& processor)
    : drumProcessor(processor)
{
    loadButton.setButtonText("Load");
    saveButton.setButtonText("Save");
    fineTuneButton.setButtonText("Fine Tune");
    aboutButton.setButtonText("About");

    fineTuneButton.setToggleable(true);
    fineTuneButton.setClickingTogglesState(true);

    // Setup the load model button
    fileChooser =
        std::make_unique<juce::FileChooser>("File Browser", getPresetFolder(), "*.pt");
    int flags = juce::FileBrowserComponent::openMode;
    flags |= juce::FileBrowserComponent::canSelectFiles;
    loadButton.onClick = [this, flags]
    {
        fileChooser->launchAsync(flags,
                                 [this](const juce::FileChooser& chooser)
                                 { chooserCallback(chooser); });
    };

    addAndMakeVisible(loadButton);
    addAndMakeVisible(saveButton);
    addAndMakeVisible(fineTuneButton);
    addAndMakeVisible(aboutButton);
}

void ButtonControlComponent::resized()
{
    loadButton.setBounds(buttonContol1Bounds);
    saveButton.setBounds(buttonContol2Bounds);
    fineTuneButton.setBounds(buttonContol3Bounds);
    aboutButton.setBounds(buttonContol4Bounds);
}

juce::File ButtonControlComponent::getPresetFolder()
{
    auto appDir = juce::File::commonApplicationDataDirectory;
    juce::String presetFolder =
        juce::File::getSpecialLocation(appDir).getFullPathName();

    presetFolder += juce::File::getSeparatorString() + SupportFolder;
    presetFolder += juce::File::getSeparatorString() + AppFolder;
    presetFolder += juce::File::getSeparatorString() + PresetFolder;
    presetFolder += juce::File::getSeparatorString() + FactoryFolder;

    return juce::File(presetFolder);
}

void ButtonControlComponent::chooserCallback(const juce::FileChooser& chooser)
{
    auto result = chooser.getResult();
    auto resultPath = result.getFullPathName().toStdString();
    drumProcessor.getSynthController().updateModel(resultPath);
}
