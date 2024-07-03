#pragma once

#include "BinaryData.h"
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
