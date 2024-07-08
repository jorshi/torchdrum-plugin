#include "SynthControlComponent.h"

SynthControlComponent::SynthControlComponent()
{
    knobRow1.setNumKnobs(4);
    knobRow1.setLabelText("Oscillator 1");
    addAndMakeVisible(knobRow1);

    knobRow2.setNumKnobs(4);
    knobRow2.setLabelText("Oscillator 2");
    addAndMakeVisible(knobRow2);

    knobRow3.setNumKnobs(4);
    knobRow3.setLabelText("Filtered Noise");
    addAndMakeVisible(knobRow3);

    knobRow4.setNumKnobs(4);
    knobRow4.setLabelText("Global Controls");
    addAndMakeVisible(knobRow4);
}

void SynthControlComponent::paint(juce::Graphics& g)
{
    // Draw the knob rows
    auto rowHeight = getKnobRowComponentHeight(getWidth(), 4);
    auto padding = (int) getKnobRowPadding(rowHeight);
    knobRow1.setBounds(0, 0, getWidth(), rowHeight);
    knobRow2.setBounds(0, rowHeight + padding, getWidth(), rowHeight);
    knobRow3.setBounds(0, (rowHeight + padding) * 2, getWidth(), rowHeight);
    knobRow4.setBounds(0, (rowHeight + padding) * 3, getWidth(), rowHeight);
}
