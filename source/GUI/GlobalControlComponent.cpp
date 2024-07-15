#include "GlobalControlComponent.h"
#include "TorchDrumStyle.h"

GlobalControlComponent::GlobalControlComponent(TorchDrumProcessor& processor)
    : drumProcessor(processor)
{
}

void GlobalControlComponent::paint(juce::Graphics& g)
{
    g.setColour(vizualizerGradientColourB);
    g.fillRect(getLocalBounds());
    g.setColour(borderColour);
    g.drawRect(getLocalBounds(), 1);
}
