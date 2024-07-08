#include "DualKnobComponent.h"

InnerKnobLookAndFeel::InnerKnobLookAndFeel() {}

void InnerKnobLookAndFeel::drawRotarySlider(juce::Graphics& g,
                                            int x,
                                            int y,
                                            int width,
                                            int height,
                                            float sliderPos,
                                            float rotaryStartAngle,
                                            float rotaryEndAngle,
                                            [[maybe_unused]] juce::Slider& slider)
{
    auto bounds = juce::Rectangle<float>(x, y, width, height).toFloat();
    auto centre = bounds.getCentre();
    auto stroke = getInnerKnobStrokeWidth((float) width);

    g.saveState();

    sliderPos = sliderPos - 0.5f;
    g.addTransform(juce::AffineTransform::rotation(
        sliderPos * (rotaryEndAngle - rotaryStartAngle), centre.getX(), centre.getY()));

    // Draw the radial gradient fill
    auto gradient = juce::ColourGradient(
        innerKnobColourA, centre.getX(), centre.getY(), innerKnobColourB, 0, 0, true);
    g.setGradientFill(gradient);
    g.fillEllipse(bounds.reduced(stroke));

    // Draw the dial knob border
    g.setColour(borderColour);
    g.drawEllipse(bounds.reduced(stroke / 2.0f), stroke);

    // Draw the tick mark
    auto tickLength = getInnerKnobTickLength((float) width);
    auto tickStart = height / 2.0f - tickLength;
    g.setOrigin(juce::Point<int>((int) centre.getX(), (int) centre.getY()));
    g.drawRoundedRectangle(
        juce::Rectangle<float>(
            -stroke / 4.0f, -tickStart, stroke / 2.0f, -(tickLength - stroke)),
        stroke / 8.0f,
        stroke / 1.5f);

    g.restoreState();
}

//==============================================================================
OuterKnobLookAndFeel::OuterKnobLookAndFeel() {}

void OuterKnobLookAndFeel::drawRotarySlider(juce::Graphics& g,
                                            int x,
                                            int y,
                                            int width,
                                            int height,
                                            float sliderPos,
                                            float rotaryStartAngle,
                                            float rotaryEndAngle,
                                            [[maybe_unused]] juce::Slider& slider)
{
    auto bounds = juce::Rectangle<float>(x, y, width, height).toFloat();
    auto centre = bounds.getCentre();
    auto stroke = getOuterKnobStrokeWidth((float) width);

    g.saveState();

    // Add the background ring
    juce::Path ring;
    ring.addPieSegment(
        bounds.reduced(stroke / 2.0f), 0.0f, juce::MathConstants<float>::twoPi, 0.64f);

    g.setColour(outerKnobColourA);
    g.fillPath(ring);

    // Add the modulation ring
    // TODO: how to make the modulation ring rotate with the inner knob?
    juce::Path modulation;
    auto rotarySize = rotaryEndAngle - rotaryStartAngle;
    auto modCentre = (offset - 0.5f) * rotarySize;
    auto modStart = modCentre - rotarySize * 0.5f * sliderPos;
    auto modEnd = modStart + rotarySize * sliderPos;

    modStart = juce::jmax(modStart, -0.5f * rotarySize);
    modEnd = juce::jmin(modEnd, 0.5f * rotarySize);

    modulation.addPieSegment(bounds.reduced(stroke / 2.0f), modStart, modEnd, 0.655f);

    // Draw the radial gradient fill for the modulation ring
    g.setGradientFill(juce::ColourGradient(
        modKnobColourA, centre.getX(), centre.getY(), modKnobColourB, 0.0, 0.0, true));
    g.fillPath(modulation);

    // Draw the dial knob border
    g.setColour(borderColour);
    g.drawEllipse(bounds.reduced(stroke / 2.0f), stroke);
    g.strokePath(modulation, juce::PathStrokeType(stroke));

    // Draw the modulated parameter tick mark
    auto tickLength = getOuterKnobTickLength((float) width);
    auto tickStart = height / 2.0f - tickLength * 0.8f;
    auto tickRotation = (modulatedValue - 0.5f) * rotarySize;

    // Rotate the tick mark with respect to the centre
    g.setOrigin(juce::Point<int>((int) centre.getX(), (int) centre.getY()));
    g.addTransform(juce::AffineTransform::rotation(tickRotation, 0.0, 0.0));
    g.drawRoundedRectangle(
        juce::Rectangle<float>(
            -stroke / 4.0f, -tickStart, stroke / 2.0f, -(tickLength * 0.6f - stroke)),
        stroke / 8.0f,
        stroke / 1.5f);

    g.restoreState();
}

//==============================================================================
DualKnobComponent::DualKnobComponent()
{
    outerKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    outerKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    outerKnob.setLookAndFeel(&outerKnobLookAndFeel);
    addAndMakeVisible(outerKnob);

    innerKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    innerKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    innerKnob.setLookAndFeel(&innerKnobLookAndFeel);
    addAndMakeVisible(innerKnob);
    innerKnob.addListener(this);

    textBox.setText("Freq", juce::dontSendNotification);
    textBox.setColour(juce::Label::textColourId, juce::Colours::black);
    textBox.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(textBox);

    valueBox.setText(innerKnob.getTextFromValue(innerKnob.getValue()),
                     juce::dontSendNotification);
    valueBox.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(valueBox);

    fontOptions = getPluginFont();

    // Set value of modulated parameter -- this should be set by the synth
    outerKnobLookAndFeel.setModulatedValue(0.5f);

    // Add a deep listener that includes all children components
    this->addMouseListener(this, true);
}

void DualKnobComponent::paint([[maybe_unused]] juce::Graphics& g)
{
    // Draw the textbox at the top
    textBox.setBounds(textBoxBounds);

    // Draw the value box over the textbox
    valueBox.setBounds(textBoxBounds);

    // Draw the outer knob
    outerKnob.setBounds(outerKnobBounds);
    innerKnob.setBounds(innerKnobBounds);

    // Draw the text box outline in the hover state
    if (mouseOver)
    {
        g.setColour(borderColour);
        g.fillRect(leftTextBoxLine);
        g.fillRect(rightTextBoxLine);
    }
}

void DualKnobComponent::resized()
{
    // Update the inner component positions
    auto width = getWidth();
    auto height = getHeight();

    // Target height for the textbox and padding
    int textBoxHeight = (int) getDualKnobTextBoxHeight(width);
    int textWithPadding = textBoxHeight + (int) getDualKnobPadding(width);
    textBoxBounds = juce::Rectangle<int>(0, 0, width, textBoxHeight);

    // Outer knob bounds
    int outerKnobSize = height - textWithPadding;
    int outerKnobX = (int) ((width - outerKnobSize) / 2.0f);
    outerKnobBounds =
        juce::Rectangle<int>(outerKnobX, textWithPadding, outerKnobSize, outerKnobSize);

    // Inner knob bounds
    int innerKnobSize = (int) (outerKnobSize * 0.66);
    int innerKnobX = (int) ((width - innerKnobSize) / 2.0f);
    int innerKnobY = textWithPadding + (int) ((outerKnobSize - innerKnobSize) / 2.0f);
    innerKnobBounds =
        juce::Rectangle<int>(innerKnobX, innerKnobY, innerKnobSize, innerKnobSize);

    // Update the font size
    juce::Font font(fontOptions);
    textBox.setFont(font.withHeight(getTextHeight((float) textBoxHeight)));
    valueBox.setFont(font.withHeight(getTextHeight((float) textBoxHeight)));

    // Lines for textbox border during hover state
    auto thickness = getDualKnobThinStrokeWidth((float) width);
    auto lineHeight = textBoxBounds.getHeight() - 2 * thickness;
    leftTextBoxLine = juce::Rectangle<int>(
        textBoxBounds.getX(), textBoxBounds.getY() + thickness, thickness, lineHeight);
    rightTextBoxLine = juce::Rectangle<int>(textBoxBounds.getRight() - thickness,
                                            textBoxBounds.getY() + thickness,
                                            thickness,
                                            lineHeight);
}

void DualKnobComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &innerKnob)
    {
        auto innerValue = juce::jmap(innerKnob.getValue(),
                                     innerKnob.getMinimum(),
                                     innerKnob.getMaximum(),
                                     0.0,
                                     1.0);
        outerKnobLookAndFeel.setOffset((float) innerValue);
        outerKnob.repaint();

        // Update the value box
        valueBox.setText(innerKnob.getTextFromValue(innerKnob.getValue()),
                         juce::dontSendNotification);
        valueBox.repaint();
    }
}

void DualKnobComponent::sliderDragStarted(juce::Slider* slider)
{
    if (slider == &innerKnob)
    {
        // innerKnobLookAndFeel.setMouseOver(true);
        // innerKnob.repaint();
    }
}

void DualKnobComponent::sliderDragEnded(juce::Slider* slider)
{
    if (slider == &innerKnob)
    {
        // innerKnobLookAndFeel.setMouseOver(false);
        // innerKnob.repaint();
    }
}

void DualKnobComponent::mouseEnter(const juce::MouseEvent& event)
{
    // Update the text box border when over the component
    if (! mouseOver)
    {
        mouseOver = true;
        repaint();
    }
}

void DualKnobComponent::mouseExit(const juce::MouseEvent& event)
{
    // Update the text box border when leaving the component
    // Could there be a race condition here is leaving an innerKnob and moving
    // into the outerBnob or parent component?
    if (mouseOver)
    {
        mouseOver = false;
        repaint();
    }
}
