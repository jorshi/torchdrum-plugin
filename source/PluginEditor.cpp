#include "PluginEditor.h"
#include "GUI/TorchDrumStyle.h"
#include "PluginProcessor.h"

TorchDrumEditor::TorchDrumEditor(TorchDrumProcessor& p)
    : AudioProcessorEditor(&p),
      drumProcessor(p),
      onsetControlComponent(p),
      synthControlComponent(p),
      visualizerComponent(p)
{
    fileChooser =
        std::make_unique<juce::FileChooser>("File Browser", getPresetFolder(), "*.pt");

    // Add the action listener to the SynthController
    drumProcessor.getSynthController().getBroadcaster().addActionListener(this);

    // Plugin window size and resizable settings
    setSize(fullPluginWidth, fullPluginHeight);
    setResizable(true, true);
    setResizeLimits(
        fullPluginWidth, fullPluginHeight, fullPluginWidth * 2, fullPluginHeight * 2);

    // Set the constrainer aspect ratio
    auto* constrainer = getConstrainer();
    constrainer->setFixedAspectRatio(fullPluginWidth / fullPluginHeight);

    // Load the background image
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::background2x_png,
                                                      BinaryData::background2x_pngSize);

    // Add GUI Components
    addAndMakeVisible(onsetControlComponent);
    addAndMakeVisible(synthControlComponent);
    addAndMakeVisible(visualizerComponent);
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

    // Draw the SynthControlComponent
    int width = getWidth();
    int height = getHeight();
    int controlX = (int) getSynthControlComponentX(width);
    int controlY = (int) getSynthControlComponentY(height);
    int controlWidth = getSynthControlComponentWidth(getWidth());
    int controlHeight = height - controlY;
    synthControlComponent.setBounds(controlX, controlY, controlWidth, controlHeight);
}

void TorchDrumEditor::resized()
{
    onsetControlComponent.setBounds(getOnsetControlComponentBounds(getWidth()));
    visualizerComponent.setBounds(getVisualizerBounds(getWidth()));
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
