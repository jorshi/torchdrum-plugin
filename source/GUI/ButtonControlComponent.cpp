#include "ButtonControlComponent.h"
#include "TorchDrumStyle.h"

ButtonControlComponent::ButtonControlComponent(TorchDrumProcessor& processor)
    : drumProcessor(processor)
{
}

void ButtonControlComponent::paint(juce::Graphics& g)
{
    g.setColour(vizualizerGradientColourB);
    g.fillRect(getLocalBounds());
    g.setColour(borderColour);
    g.drawRect(getLocalBounds(), 1);
}
