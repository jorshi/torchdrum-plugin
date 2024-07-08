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
    void resized() override;

    // Slider listener
    void sliderValueChanged(juce::Slider* slider) override;
    void sliderDragStarted(juce::Slider* slider) override;
    void sliderDragEnded(juce::Slider* slider) override;

    // Mouse listener
    void mouseEnter(const juce::MouseEvent& event) override;
    void mouseExit(const juce::MouseEvent& event) override;

private:
    InnerKnobLookAndFeel innerKnobLookAndFeel;
    OuterKnobLookAndFeel outerKnobLookAndFeel;
    juce::Slider innerKnob;
    juce::Slider outerKnob;
    juce::Label textBox;
    juce::Label valueBox;
    juce::FontOptions fontOptions;

    // Layout
    juce::Rectangle<int> outerKnobBounds;
    juce::Rectangle<int> innerKnobBounds;
    juce::Rectangle<int> textBoxBounds;
    juce::Rectangle<int> leftTextBoxLine;
    juce::Rectangle<int> rightTextBoxLine;

    std::atomic<bool> mouseOver = false;
    std::atomic<bool> dragging = false;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DualKnobComponent)
};
