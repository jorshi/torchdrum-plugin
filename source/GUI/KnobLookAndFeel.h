#pragma once

#include "juce_gui_basics/juce_gui_basics.h"

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
    void drawFineTuneKnob(juce::Graphics& g,
                          juce::Rectangle<float>& bounds,
                          float sliderPos,
                          float rotaryStartAngle,
                          float rotaryEndAngle,
                          juce::Slider& slider);

    void setOffset(float newValue) { offset = newValue; }
    void setModulatedValue(float newValue) { modulatedValue = newValue; }
    void setFineTune(bool newValue) { fineTune = newValue; }

private:
    float offset = 0.0f;
    float modulatedValue = 0.0f;
    bool fineTune = false;
};
