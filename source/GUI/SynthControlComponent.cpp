#include "SynthControlComponent.h"

SynthControlComponent::SynthControlComponent() {}

void SynthControlComponent::paint(juce::Graphics& g)
{
    // Bounding box for development purposes
    g.setColour(juce::Colours::black);
    g.drawRect(0, 0, getWidth(), getHeight());
}
