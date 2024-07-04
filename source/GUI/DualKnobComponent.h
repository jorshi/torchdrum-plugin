#pragma once

#include "BinaryData.h"
#include "TorchDrumStyle.h"
#include "juce_gui_basics/juce_gui_basics.h"

class DualKnobLookAndFeel : public juce::LookAndFeel_V4
{
public:
    DualKnobLookAndFeel() {}

    void drawRotarySlider(juce::Graphics& g,
                          int x,
                          int y,
                          int width,
                          int height,
                          float sliderPos,
                          float rotaryStartAngle,
                          float rotaryEndAngle,
                          juce::Slider& slider) override
    {
        auto bounds = juce::Rectangle<float>(x, y, width, height).toFloat();
        auto centre = bounds.getCentre();
        auto stroke = getInnerKnobStrokeWidth((float) width);

        g.saveState();

        sliderPos = sliderPos - 0.5;
        g.addTransform(juce::AffineTransform::rotation(
            sliderPos * (rotaryEndAngle - rotaryStartAngle),
            centre.getX(),
            centre.getY()));

        // Draw the radial gradient fill
        auto gradient = juce::ColourGradient(innerKnobColourA,
                                             centre.getX(),
                                             centre.getY(),
                                             innerKnobColourB,
                                             0,
                                             0,
                                             true);
        g.setGradientFill(gradient);
        g.fillEllipse(bounds.reduced(stroke));

        // Draw the dial knob border
        g.setColour(borderColour);
        g.drawEllipse(bounds.reduced(stroke / 2.0f), stroke);

        // Draw the tick mark
        auto tickLength = getInnerKnobTickLength((float) width);
        auto tickStart = height / 2.0f - tickLength;
        g.setOrigin(juce::Point<int>(centre.getX(), centre.getY()));
        // g.addTransform(juce::AffineTransform::rotation(sliderPos * (rotaryEndAngle - rotaryStartAngle), 0, 0));
        g.drawRoundedRectangle(
            juce::Rectangle<float>(
                -stroke / 4.0f, -tickStart, stroke / 2.0f, -(tickLength - stroke)),
            stroke / 8.0f,
            stroke / 1.5f);

        g.restoreState();
    }

private:
    std::unique_ptr<juce::Drawable> knobSVG;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DualKnobLookAndFeel)
};

class DualKnobComponent : public juce::Component
{
public:
    DualKnobComponent();

    void paint(juce::Graphics& g) override;

private:
    DualKnobLookAndFeel lookAndFeel;
    juce::Slider innerKnob;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DualKnobComponent)
};
