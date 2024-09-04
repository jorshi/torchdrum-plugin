#include "KnobLookAndFeel.h"
#include "TorchDrumStyle.h"

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
    auto stroke = knobStrokeWidth;

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
    auto stroke = knobStrokeWidth;

    g.saveState();

    // Add the background ring
    juce::Path ring;
    ring.addPieSegment(
        bounds.reduced(stroke / 2.0f), 0.0f, juce::MathConstants<float>::twoPi, 0.655f);

    g.setColour(outerKnobColourA);
    g.fillPath(ring);

    // Draw the fine-tune knob (if applicable)
    if (fineTune)
    {
        drawFineTuneKnob(
            g, bounds, sliderPos, rotaryStartAngle, rotaryEndAngle, slider);
    }
    else
    {
        drawModulation(g, bounds, rotaryStartAngle, rotaryEndAngle);
    }

    // Draw the dial knob border
    g.setColour(borderColour);
    g.drawEllipse(bounds.reduced(stroke / 2.0f), stroke);
    g.strokePath(ring, juce::PathStrokeType(stroke));

    g.restoreState();
}

void OuterKnobLookAndFeel::drawFineTuneKnob(juce::Graphics& g,
                                            juce::Rectangle<float>& bounds,
                                            float sliderPos,
                                            float rotaryStartAngle,
                                            float rotaryEndAngle,
                                            [[maybe_unused]] juce::Slider& slider)
{
    g.saveState();

    auto centre = bounds.getCentre();
    auto stroke = knobStrokeWidth;

    // Add the modulation ring
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

    // Draw the modulated parameter tick mark
    auto tickLength = getOuterKnobTickLength(bounds.getWidth());
    auto tickStart = bounds.getHeight() / 2.0f - tickLength * 0.8f;
    auto tickRotation = (modulatedValue - 0.5f) * rotarySize;

    // Rotate the tick mark with respect to the centre
    g.setColour(borderColour);
    g.setOrigin(juce::Point<int>((int) centre.getX(), (int) centre.getY()));
    g.addTransform(juce::AffineTransform::rotation(tickRotation, 0.0, 0.0));
    g.drawRoundedRectangle(
        juce::Rectangle<float>(
            -stroke / 4.0f, -tickStart, stroke / 2.0f, -(tickLength * 0.6f - stroke)),
        stroke / 8.0f,
        stroke / 1.5f);

    g.restoreState();
}

void OuterKnobLookAndFeel::drawModulation(juce::Graphics& g,
                                          juce::Rectangle<float>& bounds,
                                          float rotaryStartAngle,
                                          float rotaryEndAngle)
{
    g.saveState();

    auto centre = bounds.getCentre();
    auto stroke = knobStrokeWidth;
    auto rotarySize = rotaryEndAngle - rotaryStartAngle;

    // Draw the modulated parameter tick mark
    auto tickLength = dualKnobOuterTickLength;
    auto tickStart = bounds.getHeight() / 2.0f - tickLength;
    auto tickRotation = (modulatedValue - 0.5f) * rotarySize;

    // Rotate the tick mark with respect to the centre
    g.setColour(borderColour);
    g.setOrigin(juce::Point<int>((int) centre.getX(), (int) centre.getY()));
    g.addTransform(juce::AffineTransform::rotation(tickRotation, 0.0, 0.0));
    g.drawRoundedRectangle(
        juce::Rectangle<float>(
            -stroke / 4.0f, -tickStart, stroke / 2.0f, -(tickLength * 1.0f - stroke)),
        stroke / 8.0f,
        stroke / 1.5f);

    g.restoreState();
}
