#include "DualKnobComponent.h"

//==============================================================================
DualKnobComponent::DualKnobComponent(juce::RangedAudioParameter* p,
                                     juce::NormalisableRange<double> range,
                                     KnobType knobType)
    : parameter(p), innerKnob(p, range)
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

    // Set value of modulated parameter -- this should be set by the synth
    outerKnobLookAndFeel.setModulatedValue(0.5f);

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
        textBoxBounds = dualKnobTextBoxBounds;
        leftTextBoxLine = dualKnobTextOutlineLeft;
        rightTextBoxLine = dualKnobTextOutlineRight;

        // Update the font size
        juce::Font font(fontOptions);
        textBox.setFont(font.withHeight(dualKnobTextBoxBounds.getHeight()));
        valueBox.setFont(font.withHeight(dualKnobTextBoxBounds.getHeight()));
    }
    else if (knobType == KnobType::SingleSmall)
    {
        innerKnob.setBounds(singleSmallKnobOuterKnobBounds);
        textBox.setBounds(singleSmallKnobTextBoxBounds);
        valueBox.setBounds(singleSmallKnobTextBoxBounds);
        textBoxBounds = singleSmallKnobTextBoxBounds;

        // Update the font size
        juce::Font font(fontOptions);
        auto textHeight = singleSmallKnobTextBoxBounds.getHeight() / 2 - 4;
        textBox.setFont(font.withHeight(textHeight));
        textBox.setJustificationType(juce::Justification::centredTop);
        textBox.setBorderSize(juce::BorderSize<int>(0));

        valueBox.setFont(font.withHeight(dualKnobTextBoxBounds.getHeight()));
    }
}

void DualKnobComponent::paint(juce::Graphics& g)
{
    // Draw the value box over if dragging
    if (dragging)
    {
        // Draw a rectangle behind the value box
        g.setColour(knobValueBackground);
        g.fillRect(textBoxBounds);

        // Draw the border
        g.setColour(borderColour);
        g.drawRect(textBoxBounds, dualKnobThinStrokeWidth);

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

void DualKnobComponent::resized()
{
    // // Update the inner component positions
    // auto width = getWidth();
    // auto height = getHeight();

    // // Target height for the textbox and padding
    // int textBoxHeight = (int) getDualKnobTextBoxHeight(width);
    // int textWithPadding = textBoxHeight + (int) getDualKnobPadding(width);
    // textBoxBounds = juce::Rectangle<int>(0, 0, width, textBoxHeight);
    // textBox.setBounds(textBoxBounds);
    // valueBox.setBounds(textBoxBounds);

    // // Outer knob bounds
    // int outerKnobSize = height - textWithPadding;
    // int outerKnobX = (int) ((width - outerKnobSize) / 2.0f);
    // outerKnobBounds =
    //     juce::Rectangle<int>(outerKnobX, textWithPadding, outerKnobSize, outerKnobSize);
    // outerKnob.setBounds(outerKnobBounds);

    // // Inner knob bounds
    // int innerKnobSize = (int) (outerKnobSize * (2.0 / 3.0));
    // int innerKnobX = (int) ((width - innerKnobSize) / 2.0f);
    // int innerKnobY = textWithPadding + (int) ((outerKnobSize - innerKnobSize) / 2.0f);
    // innerKnobBounds =
    //     juce::Rectangle<int>(innerKnobX, innerKnobY, innerKnobSize, innerKnobSize);
    // innerKnob.setBounds(innerKnobBounds);

    // // Update the font size
    // juce::Font font(fontOptions);
    // textBox.setFont(font.withHeight(getTextHeight((float) textBoxHeight)));
    // valueBox.setFont(font.withHeight(getTextHeight((float) textBoxHeight)));

    // // Lines for textbox border during hover state
    // int thickness = (int) getDualKnobThinStrokeWidth((float) width);
    // int lineHeight = (int) (textBoxBounds.getHeight() - 2.0f * thickness);
    // leftTextBoxLine = juce::Rectangle<int>(
    //     textBoxBounds.getX(), textBoxBounds.getY() + thickness, thickness, lineHeight);
    // rightTextBoxLine = juce::Rectangle<int>(textBoxBounds.getRight() - thickness,
    //                                         textBoxBounds.getY() + thickness,
    //                                         thickness,
    //                                         lineHeight);
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
