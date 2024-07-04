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

    void setOffset(float newValue) { offset = newValue; }
    void setModulatedValue(float newValue) { modulatedValue = newValue; }

private:
    float offset = 0.0f;
    float modulatedValue = 0.0f;
};

//==============================================================================
class DualKnobComponent : public juce::Component, juce::Slider::Listener
{
public:
    DualKnobComponent();

    void paint(juce::Graphics& g) override;

    void sliderValueChanged(juce::Slider* slider) override;

private:
    InnerKnobLookAndFeel innerKnobLookAndFeel;
    OuterKnobLookAndFeel outerKnobLookAndFeel;
    juce::Slider innerKnob;
    juce::Slider outerKnob;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DualKnobComponent)
};
