#include "PluginEditor.h"
#include "PluginProcessor.h"

TorchDrumEditor::TorchDrumEditor(TorchDrumProcessor& p)
    : AudioProcessorEditor(&p), processor(p)
{
    // Setup the file browser
    fileChooser = std::make_unique<juce::FileChooser>(
        "File Browser",
        juce::File(),
        "*.pt");

    addAndMakeVisible(editor);
    addAndMakeVisible(loadModelButton);

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
}
