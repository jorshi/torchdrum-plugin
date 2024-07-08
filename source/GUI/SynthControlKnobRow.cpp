#include "SynthControlKnobRow.h"

SynthControlKnobRow::SynthControlKnobRow() {}

void SynthControlKnobRow::paint(juce::Graphics& g)
{
    // Bounding box for development purposes
    g.setColour(juce::Colours::black);
    g.drawRect(0, 0, getWidth(), getHeight());
}

void SynthControlKnobRow::resized()
{
    int knobWidth = getWidth() / numKnobs;
    int knobHeight = getHeight();

    for (int i = 0; i < numKnobs; i++)
    {
        knobBounds[i].setBounds(i * knobWidth, 0, knobWidth, knobHeight);
        knobs[i]->setBounds(knobBounds[i]);
    }
}

void SynthControlKnobRow::setNumKnobs(int newValue)
{
    numKnobs = newValue;
    knobBounds.clear();
    knobs.clear();

    for (int i = 0; i < numKnobs; i++)
    {
        juce::Rectangle<int> knobBounds;
        this->knobBounds.push_back(knobBounds);

        std::unique_ptr<DualKnobComponent> knob = std::make_unique<DualKnobComponent>();
        knobs.push_back(std::move(knob));
        addAndMakeVisible(knobs[i].get());
    }

    resized();
}
