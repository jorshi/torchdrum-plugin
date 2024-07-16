#include "SynthControlKnobRow.h"

SynthControlKnobRow::SynthControlKnobRow()
{
    // Load custom font
    fontOptions = getBoldPluginFont();

    // Set up the label
    addAndMakeVisible(label);
    label.setText("Knob Row", juce::dontSendNotification);
    label.setColour(juce::Label::textColourId, juce::Colours::black);
    label.setJustificationType(juce::Justification::centred);
}

void SynthControlKnobRow::paint(juce::Graphics& g)
{
    // Bounding box for development purposes
    // g.setColour(juce::Colours::black);
    // g.drawRect(0, 0, getWidth(), getHeight());

    // g.drawRect(label.getBounds());
}

void SynthControlKnobRow::resized()
{
    auto height = getHeight();

    // Update the bounds of each knob
    int knobWidth = getWidth() / numKnobs;
    int knobHeight = (int) getKnobRowKnobHeight(height);
    int knobY = height - knobHeight;
    for (int i = 0; i < numKnobs; i++)
    {
        knobBounds[i].setBounds(i * knobWidth, knobY, knobWidth, knobHeight);

        // Draw the knob if it exists
        if (knobs[i] != nullptr)
            knobs[i]->setBounds(knobBounds[i]);
    }

    // Update the bounds of the label
    auto labelHeight = (int) knobY * 0.85f;
    label.setBounds(0, 0, getWidth(), labelHeight);

    // Update the font size
    juce::Font font(fontOptions);
    label.setFont(font.withHeight(labelHeight));
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

        std::unique_ptr<DualKnobComponent> knob = nullptr;
        knobs.push_back(std::move(knob));
    }

    resized();
}

void SynthControlKnobRow::setLabelText(const juce::String& newText)
{
    label.setText(newText, juce::dontSendNotification);
}

void SynthControlKnobRow::addParameter(juce::RangedAudioParameter* parameter,
                                       juce::NormalisableRange<double> range,
                                       int index)
{
    if (index < numKnobs)
    {
        knobs[index] = std::make_unique<DualKnobComponent>(parameter, range);
        addAndMakeVisible(knobs[index].get());
        resized();
    }
}
