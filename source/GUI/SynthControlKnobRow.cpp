#include "SynthControlKnobRow.h"

SynthControlKnobRow::SynthControlKnobRow()
{
    addAndMakeVisible(label);
    label.setText("Knob Row", juce::dontSendNotification);
    label.setColour(juce::Label::textColourId, juce::Colours::black);
    label.setJustificationType(juce::Justification::centred);
}

void SynthControlKnobRow::paint(juce::Graphics& g)
{
    // Bounding box for development purposes
    g.setColour(juce::Colours::black);
    g.drawRect(0, 0, getWidth(), getHeight());
}

void SynthControlKnobRow::resized()
{
    auto height = getHeight();
    // Update the bounds of the label
    label.setBounds(0, 0, getWidth(), (int) getKnobRowLabelHeight(height));

    // Update the bounds of each knob
    int knobWidth = getWidth() / numKnobs;
    int knobHeight = (int) getKnobRowKnobHeight(height);
    int knobY = height - knobHeight;
    for (int i = 0; i < numKnobs; i++)
    {
        knobBounds[i].setBounds(i * knobWidth, knobY, knobWidth, knobHeight);
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
