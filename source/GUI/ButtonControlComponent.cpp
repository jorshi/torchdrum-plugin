#include "ButtonControlComponent.h"
#include "TorchDrumStyle.h"

ButtonControlComponent::ButtonControlComponent(TorchDrumProcessor& processor)
    : drumProcessor(processor)
{
    loadButton.setButtonText("Load");
    addAndMakeVisible(loadButton);
}

void ButtonControlComponent::paint(juce::Graphics& g)
{
    // g.setColour(vizualizerGradientColourB);
    // g.fillRect(getLocalBounds());
    g.setColour(borderColour);
    g.drawRect(getLocalBounds(), 1);
}

void ButtonControlComponent::resized() { loadButton.setBounds(buttonContol1Bounds); }
