#include "PluginEditor.h"
#include "PluginProcessor.h"

TorchDrumEditor::TorchDrumEditor(TorchDrumProcessor& p)
    : AudioProcessorEditor(&p)
{
    // Setup the file browser
    fileChooser = std::make_unique<juce::FileChooser>(
        "File Browser",
        juce::File(),
        "*.pt");

    addAndMakeVisible(editor);
    addAndMakeVisible(loadModelButton);

    auto flags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles;
    loadModelButton.onClick = [this, flags]
    {
        fileChooser->launchAsync(flags,
                                 [this](const juce::FileChooser& chooser)
                                 {
                                     auto result = chooser.getResult();
                                     DBG(result.getFullPathName());
                                 });
    };

    setSize(400, 500);
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
