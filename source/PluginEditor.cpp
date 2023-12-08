#include "PluginEditor.h"
#include "PluginProcessor.h"

TorchDrumEditor::TorchDrumEditor(TorchDrumProcessor& p)
    : AudioProcessorEditor(&p), processor(p)
{
    fileChooser = std::make_unique<juce::FileChooser>(
        "File Browser",
        getPresetFolder(),
        "*.pt");

    addAndMakeVisible(editor);
    addAndMakeVisible(loadModelButton);
    addAndMakeVisible(resetNormButton);

    // Setup the load model button
    int flags = juce::FileBrowserComponent::openMode;
    flags |= juce::FileBrowserComponent::canSelectFiles;
    loadModelButton.onClick = [this, flags]
    {
        fileChooser->launchAsync(flags,
                                 [this](const juce::FileChooser& chooser)
                                 {
                                     chooserCallback(chooser);
                                 });
    };

    // Setup the reset normalizer button
    resetNormButton.onClick = [this]
    {
        processor.getSynthController().resetFeatureNormalizers();
    };

    setSize(400, 500);
}

void TorchDrumEditor::chooserCallback(const juce::FileChooser& chooser)
{
    auto result = chooser.getResult();
    auto resultPath = result.getFullPathName().toStdString();
    processor.getSynthController().updateModel(resultPath);
}

void TorchDrumEditor::paint(juce::Graphics& g)
{
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void TorchDrumEditor::resized()
{
    auto area = getLocalBounds();
    area = area.withTrimmedTop(90);
    editor.setBounds(area);

    loadModelButton.setBounds(25, 20, 100, 50);
    resetNormButton.setBounds(150, 20, 150, 50);
}

juce::File TorchDrumEditor::getPresetFolder()
{
    auto appDir = juce::File::commonApplicationDataDirectory;
    juce::String presetFolder = juce::File::getSpecialLocation(appDir).getFullPathName();

    presetFolder += juce::File::getSeparatorString() + SupportFolder;
    presetFolder += juce::File::getSeparatorString() + AppFolder;
    presetFolder += juce::File::getSeparatorString() + PresetFolder;
    presetFolder += juce::File::getSeparatorString() + FactoryFolder;

    return juce::File(presetFolder);
}
