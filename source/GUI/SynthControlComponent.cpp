#include "SynthControlComponent.h"

SynthControlComponent::SynthControlComponent() { addAndMakeVisible(knob1); }

void SynthControlComponent::paint(juce::Graphics& g)
{
    // Bounding box for development purposes
    g.setColour(juce::Colours::black);
    g.drawRect(0, 0, getWidth(), getHeight());

    // Draw the knob
    knob1.setBounds(10, 10, 45, 45);
}
