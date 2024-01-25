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

    // Add the action listener to the SynthController
    // TODO: This is probably causing the segfault!!
    processor.getSynthController().getBroadcaster().addActionListener(this);

    setSize(400, 600);
}

TorchDrumEditor::~TorchDrumEditor()
{
    processor.getSynthController().getBroadcaster().removeActionListener(this);
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

    auto& results = processor.getSynthController().getFeatures();
    float rms = results.rmsMean.getNormalized();
    float sc = results.spectralCentroidMean.getNormalized();
    float sf = results.spectralFlatnessMean.getNormalized();
    juce::String rmsString = juce::String(rms, 2);
    juce::String scString = juce::String(sc, 2);
    juce::String sfString = juce::String(sf, 2);

    g.setFont(15.0f);
    g.setColour(juce::Colours::white);

    int width = getWidth();
    g.drawText("RMS: " + rmsString, 25, 70, width, 50, juce::Justification::left, true);
    g.drawText("Spectral Centroid: " + scString, 25, 100, width, 50, juce::Justification::left, true);
    g.drawText("Spectral Flatness: " + sfString, 25, 130, width, 50, juce::Justification::left, true);
}

void TorchDrumEditor::resized()
{
    auto area = getLocalBounds();
    area = area.withTrimmedTop(180);
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

void TorchDrumEditor::actionListenerCallback(const juce::String& message)
{
    if (message == "trigger")
    {
        this->repaint();
    }
}
