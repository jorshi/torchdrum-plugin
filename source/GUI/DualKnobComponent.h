#pragma once

#include "BinaryData.h"
#include "TorchDrumStyle.h"
#include "juce_gui_basics/juce_gui_basics.h"

//==============================================================================
class InnerKnobLookAndFeel : public juce::LookAndFeel_V4
{
public:
    InnerKnobLookAndFeel();

    void drawRotarySlider(juce::Graphics& g,
                          int x,
                          int y,
                          int width,
                          int height,
                          float sliderPos,
                          float rotaryStartAngle,
                          float rotaryEndAngle,
                          juce::Slider& slider) override;
};

//==============================================================================
class OuterKnobLookAndFeel : public juce::LookAndFeel_V4
{
public:
    OuterKnobLookAndFeel();

    void drawRotarySlider(juce::Graphics& g,
                          int x,
                          int y,
                          int width,
                          int height,
                          float sliderPos,
                          float rotaryStartAngle,
                          float rotaryEndAngle,
                          juce::Slider& slider) override;
};

//==============================================================================
class DualKnobComponent : public juce::Component
{
public:
    DualKnobComponent();

    void paint(juce::Graphics& g) override;

private:
    InnerKnobLookAndFeel innerKnobLookAndFeel;
    OuterKnobLookAndFeel outerKnobLookAndFeel;
    juce::Slider innerKnob;
    juce::Slider outerKnob;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DualKnobComponent)
};
