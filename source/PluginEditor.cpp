#include "PluginEditor.h"
#include "GUI/TorchDrumStyle.h"
#include "PluginProcessor.h"

TorchDrumEditor::TorchDrumEditor(TorchDrumProcessor& p)
    : AudioProcessorEditor(&p), drumProcessor(p), pluginInterface(p)
{
    fileChooser =
        std::make_unique<juce::FileChooser>("File Browser", getPresetFolder(), "*.pt");

    // Add the action listener to the SynthController
    drumProcessor.getSynthController().getBroadcaster().addActionListener(this);

    // Plugin window size and resizable settings
    setSize((int) fullPluginWidth, (int) fullPluginHeight);
    setResizable(true, true);
    setResizeLimits((int) fullPluginWidth,
                    (int) fullPluginHeight,
                    (int) (fullPluginWidth * 2.0f),
                    (int) (fullPluginHeight * 2.0f));

    // Set the constrainer aspect ratio
    auto* constrainer = getConstrainer();
    constrainer->setFixedAspectRatio(fullPluginWidth / fullPluginHeight);

    // Load the background image
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::background2x_png,
                                                      BinaryData::background2x_pngSize);

    backgroundOverlay = juce::ImageCache::getFromMemory(
        BinaryData::backgroundOverlay2x_png, BinaryData::backgroundOverlay2x_pngSize);

    pluginInterface.setBounds(0, 0, (int) fullPluginWidth, (int) fullPluginHeight);
    addAndMakeVisible(pluginInterface);
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
    auto backgroundImageScaled = backgroundImage.rescaled(getWidth(), getHeight());
    auto backgroundOverlayScaled = backgroundOverlay.rescaled(getWidth(), getHeight());
    g.drawImageAt(backgroundImageScaled, 0, 0);
    g.drawImageAt(backgroundOverlayScaled, 0, 0);
}

void TorchDrumEditor::resized()
{
    float scale = getWidth() / fullPluginWidth;
    pluginInterface.setTransform(juce::AffineTransform::scale(scale));
}

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
