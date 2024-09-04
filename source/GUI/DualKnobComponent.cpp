#include "DualKnobComponent.h"

//==============================================================================
DualKnobComponent::DualKnobComponent(juce::RangedAudioParameter* p,
                                     juce::NormalisableRange<double> r,
                                     KnobType knobType)
    : parameter(p), range(r), innerKnob(p, r)
{
    if (knobType == KnobType::Dual)
    {
        outerKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
        outerKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        outerKnob.setLookAndFeel(&outerKnobLookAndFeel);
        addAndMakeVisible(outerKnob);
    }

    innerKnob.setLookAndFeel(&innerKnobLookAndFeel);
    auto& innerSlider = innerKnob.getSlider();
    innerSlider.addListener(this);
    addAndMakeVisible(innerKnob);

    textBox.setText(parameter->getName(24), juce::dontSendNotification);
    textBox.setColour(juce::Label::textColourId, juce::Colours::black);
    textBox.setJustificationType(juce::Justification::centred);
    textBox.setMinimumHorizontalScale(1.0);
    addAndMakeVisible(textBox);

    valueBox.setText(innerSlider.getTextFromValue(innerSlider.getValue()),
                     juce::dontSendNotification);
    valueBox.setColour(juce::Label::textColourId, juce::Colours::black);
    valueBox.setJustificationType(juce::Justification::centred);
    valueBox.setEditable(true, false, true);
    addAndMakeVisible(valueBox);
    valueBox.setVisible(false);

    // Load custom font
    fontOptions = getPluginFont();

    // Set default value of modulated parameter
    this->setModulatedValue((float) parameter->getValue());

    // Add a deep listener that includes all children components
    this->addMouseListener(this, true);

    // Set the layout based on the knob type
    setLayout(knobType);
}

void DualKnobComponent::setLayout(KnobType knobType)
{
    if (knobType == KnobType::Dual)
    {
        outerKnob.setBounds(dualKnobOuterKnobBounds);
        innerKnob.setBounds(dualKnobInnerKnobBounds);
        textBox.setBounds(dualKnobTextBoxBounds);
        valueBox.setBounds(dualKnobTextBoxBounds);
        leftTextBoxLine = dualKnobTextOutlineLeft;
        rightTextBoxLine = dualKnobTextOutlineRight;

        // Update the font size
        juce::Font font(fontOptions);
        textBox.setFont(font.withHeight(dualKnobTextBoxBounds.getHeight()));
        valueBox.setFont(font.withHeight(dualKnobTextBoxBounds.getHeight()));
    }
    else if (knobType == KnobType::SingleSmall)
    {
        innerKnob.setBounds(singleSmallKnobInnerKnobBounds);
        textBox.setBounds(singleSmallKnobTextBoxBounds);
        valueBox.setBounds(singleSmallKnobValueBoxBounds);
        leftTextBoxLine = singleSmallKnobTextOutlineLeft;
        rightTextBoxLine = singleSmallKnobTextOutlineRight;

        // Update the font size
        juce::Font font(fontOptions);
        auto textHeight = singleSmallKnobTextBoxBounds.getHeight() / 2 - 2;
        textBox.setFont(font.withHeight(textHeight));
        textBox.setJustificationType(juce::Justification::centredTop);
        textBox.setBorderSize(juce::BorderSize<int>(0));

        valueBox.setFont(font.withHeight(singleSmallKnobValueBoxBounds.getHeight()));
    }
    else if (knobType == KnobType::SingleLarge)
    {
        innerKnob.setBounds(singleLargeKnobInnerKnobBounds);
        textBox.setBounds(singleLargeKnobTextBoxBounds);
        valueBox.setBounds(singleLargeKnobTextBoxBounds);
        leftTextBoxLine = singleLargeKnobTextOutlineLeft;
        rightTextBoxLine = singleLargeKnobTextOutlineRight;

        juce::Font font(fontOptions);
        textBox.setFont(font.withHeight(singleLargeKnobTextBoxBounds.getHeight()));
        valueBox.setFont(font.withHeight(singleLargeKnobTextBoxBounds.getHeight()));
    }
}

void DualKnobComponent::paint(juce::Graphics& g)
{
    // Draw the value box over if dragging
    if (dragging)
    {
        // Draw a rectangle behind the value box
        g.setColour(knobValueBackground);
        g.fillRect(valueBox.getBounds());

        // Draw the border
        g.setColour(borderColour);
        g.drawRect(valueBox.getBounds(), dualKnobThinStrokeWidth);

        valueBox.setVisible(true);
        textBox.setVisible(false);
    }

    // Draw the text box if the valueBox is not visible
    if (! valueBox.isVisible())
    {
        // Draw the textbox at the top
        textBox.setVisible(true);

        // Draw the text box outline in the hover state
        if (mouseOver)
        {
            g.setColour(borderColour);
            g.fillRect(leftTextBoxLine);
            g.fillRect(rightTextBoxLine);
        }
    }
}

void DualKnobComponent::resized() {}

void DualKnobComponent::setTextBoxBorderSize(juce::BorderSize<int> newBorderSize)
{
    textBox.setBorderSize(newBorderSize);
    repaint();
}

void DualKnobComponent::sliderValueChanged(juce::Slider* slider)
{
    auto& innerSlider = innerKnob.getSlider();
    if (slider == &innerSlider)
    {
        auto innerValue = juce::jmap(innerSlider.getValue(),
                                     innerSlider.getMinimum(),
                                     innerSlider.getMaximum(),
                                     0.0,
                                     1.0);
        outerKnobLookAndFeel.setOffset((float) innerValue);
        outerKnob.repaint();

        // Update the value box
        valueBox.setText(innerSlider.getTextFromValue(innerSlider.getValue()),
                         juce::dontSendNotification);
        valueBox.repaint();
    }
}

void DualKnobComponent::sliderDragStarted(juce::Slider* slider)
{
    if (slider == &innerKnob.getSlider())
    {
        dragging = true;
    }
}

void DualKnobComponent::sliderDragEnded(juce::Slider* slider)
{
    if (slider == &innerKnob.getSlider())
    {
        dragging = false;
    }
}

void DualKnobComponent::mouseEnter([[maybe_unused]] const juce::MouseEvent& event)
{
    // Update the text box border when over the component
    if (! mouseOver)
    {
        mouseOver = true;
        repaint();
    }
}

void DualKnobComponent::mouseExit([[maybe_unused]] const juce::MouseEvent& event)
{
    // Update the text box border when leaving the component
    // Could there be a race condition here is leaving an innerKnob and moving
    // into the outerBnob or parent component?
    if (mouseOver)
    {
        mouseOver = false;
        valueBox.setVisible(false);
        repaint();
    }
}

void DualKnobComponent::setModulatedValue(float newValue)
{
    auto modValue = range.convertTo0to1(parameter->convertFrom0to1(newValue));
    outerKnobLookAndFeel.setModulatedValue((float) modValue);
    outerKnob.repaint();
}
