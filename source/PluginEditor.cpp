#include "PluginEditor.h"
#include "PluginProcessor.h"

TorchDrumEditor::TorchDrumEditor(TorchDrumProcessor& p)
    : AudioProcessorEditor(&p), drumProcessor(p)
{
    fileChooser =
        std::make_unique<juce::FileChooser>("File Browser", getPresetFolder(), "*.pt");

    // Add the action listener to the SynthController
    drumProcessor.getSynthController().getBroadcaster().addActionListener(this);

    // Plugin window size and resizable settings
    setSize(960, 550);
    setResizable(true, true);
    setResizeLimits(960, 550, 960 * 2, 550 * 2);

    // Load the background image
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::background2x_png,
                                                      BinaryData::background2x_pngSize);
}

TorchDrumEditor::~TorchDrumEditor()
{
    drumProcessor.getSynthController().getBroadcaster().removeActionListener(this);
}

void TorchDrumEditor::chooserCallback(const juce::FileChooser& chooser)
{
    auto result = chooser.getResult();
    auto resultPath = result.getFullPathName().toStdString();
    drumProcessor.getSynthController().updateModel(resultPath);
}

void TorchDrumEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    auto rescaledBackground = backgroundImage.rescaled(getWidth(), getHeight());
    g.drawImageAt(rescaledBackground, 0, 0);
}

void TorchDrumEditor::resized() {}

juce::File TorchDrumEditor::getPresetFolder()
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

void TorchDrumEditor::actionListenerCallback(const juce::String& message)
{
    if (message == "trigger")
    {
        this->repaint();
    }
}
