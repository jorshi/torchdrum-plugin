#include "OnsetControlComponent.h"
#include "../Parameters.h"
#include "TorchDrumStyle.h"

OnsetControlComponent::OnsetControlComponent(TorchDrumProcessor& processor)
    : drumProcessor(processor)
{
}

void OnsetControlComponent::paint(juce::Graphics& g)
{
    g.setColour(vizualizerGradientColourB);
    g.fillRect(getLocalBounds());
    g.setColour(borderColour);
    g.drawRect(getLocalBounds(), 1);
}
