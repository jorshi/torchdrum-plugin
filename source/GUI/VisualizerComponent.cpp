#include "VisualizerComponent.h"
#include "TorchDrumStyle.h"

VisualizerComponent::VisualizerComponent(TorchDrumProcessor& processor)
    : drumProcessor(processor)
{
}

void VisualizerComponent::paint(juce::Graphics& g)
{
    g.setColour(vizualizerGradientColourB);
    g.fillRect(getLocalBounds());
    g.setColour(borderColour);
    g.drawRect(getLocalBounds(), 1);
}
