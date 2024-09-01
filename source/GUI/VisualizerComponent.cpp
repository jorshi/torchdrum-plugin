#include "VisualizerComponent.h"
#include "TorchDrumStyle.h"

VisualizerComponent::VisualizerComponent(TorchDrumProcessor& processor)
    : drumProcessor(processor), onsetVisualizer(processor)
{
    resetButton.setButtonText("Reset");
    addAndMakeVisible(onsetVisualizer);
    addAndMakeVisible(featureVisualizer);
    addAndMakeVisible(resetButton);
}

void VisualizerComponent::paint(juce::Graphics& g)
{
    g.setGradientFill(gradientBackground);
    g.fillRect(featureVisualizer.getBounds());

    g.setColour(vizualizerGradientColourB);
    g.fillRect(onsetVisualizer.getBounds());

    g.setColour(borderColour);
    g.drawRect(getLocalBounds(), 1);
}

void VisualizerComponent::resized()
{
    onsetVisualizer.setBounds(
        getLocalBounds().removeFromBottom(getLocalBounds().getHeight() / 2));
    featureVisualizer.setBounds(
        getLocalBounds().removeFromTop(getLocalBounds().getHeight() / 2));
    resetButton.setBounds(resetButtonBounds);

    gradientBackground = juce::ColourGradient(vizualizerGradientColourA,
                                              getWidth() / 2.0f,
                                              getHeight() / 8.0f,
                                              vizualizerGradientColourB,
                                              getWidth() / 8.0f,
                                              0.0f,
                                              true);
}
