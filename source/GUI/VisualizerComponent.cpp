#include "VisualizerComponent.h"
#include "TorchDrumStyle.h"

VisualizerComponent::VisualizerComponent(TorchDrumProcessor& processor)
    : drumProcessor(processor), onsetVisualizer(processor)
{
    addAndMakeVisible(onsetVisualizer);
    addAndMakeVisible(featureVisualizer);
}

void VisualizerComponent::paint(juce::Graphics& g)
{
    g.setColour(vizualizerGradientColourB);
    g.fillRect(getLocalBounds());

    g.setColour(borderColour);
    g.drawRect(getLocalBounds(), 1);
}

void VisualizerComponent::resized()
{
    onsetVisualizer.setBounds(
        getLocalBounds().removeFromBottom(getLocalBounds().getHeight() / 2));
    featureVisualizer.setBounds(
        getLocalBounds().removeFromTop(getLocalBounds().getHeight() / 2));
}
