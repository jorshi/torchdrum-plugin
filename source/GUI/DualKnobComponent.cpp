#include "DualKnobComponent.h"

DualKnobComponent::DualKnobComponent()
{
    innerKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    innerKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    innerKnob.setLookAndFeel(&lookAndFeel);
    addAndMakeVisible(innerKnob);
}

void DualKnobComponent::paint(juce::Graphics& g)
{
    // Bounding box for development purposes
    g.setColour(juce::Colours::black);
    g.drawRect(0, 0, getWidth(), getHeight());

    // Draw the knob
    innerKnob.setBounds(0, 0, getWidth(), getHeight());
}
