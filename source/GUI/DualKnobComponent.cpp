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

    modulation.addPieSegment(bounds.reduced(stroke / 2.0f), modStart, modEnd, 0.65f);

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
    g.setOrigin(juce::Point<int>((int) centre.getX(), (int) centre.getY()));

    auto tickRotation = (modulatedValue - 0.5f) * rotarySize;
    g.addTransform(juce::AffineTransform::rotation(tickRotation, 0.0, 0.0));

    g.drawRoundedRectangle(
        juce::Rectangle<float>(
            -stroke / 4.0f, -tickStart, stroke / 2.0f, -(tickLength * 0.6f - stroke)),
        stroke / 8.0f,
        stroke / 1.5f);

    g.restoreState();
}

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

    // Set value of modulated parameter -- this should be set by the synth
    outerKnobLookAndFeel.setModulatedValue(0.5f);
}

void DualKnobComponent::paint([[maybe_unused]] juce::Graphics& g)
{
    // Draw the outer knob
    int outerKnobSize = getWidth();
    int outerKnobX = 0;
    outerKnob.setBounds(outerKnobX, outerKnobX, outerKnobSize, outerKnobSize);

    // Draw the inner knob over the outer knob
    int innerKnobSize = (int) (getWidth() * 0.66);
    int innerKnobX = (int) ((getWidth() - innerKnobSize) / 2.0f);
    innerKnob.setBounds(
        innerKnobX, innerKnobX, (int) innerKnobSize, (int) innerKnobSize);
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
    }
}
