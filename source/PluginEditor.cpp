#include "PluginEditor.h"
#include "PluginProcessor.h"

TorchDrumEditor::TorchDrumEditor(TorchDrumProcessor& p)
    : AudioProcessorEditor(&p)
{
    addAndMakeVisible(editor);
    setSize(400, 300);
}

void TorchDrumEditor::paint(juce::Graphics& g)
{
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void TorchDrumEditor::resized() { editor.setBounds(getLocalBounds()); }
