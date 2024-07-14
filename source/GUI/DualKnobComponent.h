#pragma once

#include "BinaryData.h"
#include "SliderParameterComponent.h"
#include "TorchDrumStyle.h"
#include "juce_gui_basics/juce_gui_basics.h"
#include <shared_plugin_helpers/shared_plugin_helpers.h>

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

//==============================================================================
class DualKnobComponent : public juce::Component, juce::Slider::Listener
{
public:
    DualKnobComponent() = delete;
    DualKnobComponent(juce::RangedAudioParameter* p);

    void paint(juce::Graphics& g) override;
    void resized() override;

    // Slider listener
    void sliderValueChanged(juce::Slider* slider) override;
    void sliderDragStarted(juce::Slider* slider) override;
    void sliderDragEnded(juce::Slider* slider) override;

    // Mouse listener
    void mouseEnter(const juce::MouseEvent& event) override;
    void mouseExit(const juce::MouseEvent& event) override;

    // Set fine-tune mode
    void setFineTune(bool newValue) { outerKnobLookAndFeel.setFineTune(newValue); }

private:
    // Parameter
    juce::RangedAudioParameter* parameter;

    InnerKnobLookAndFeel innerKnobLookAndFeel;
    OuterKnobLookAndFeel outerKnobLookAndFeel;
    SliderParameterComponent innerKnob;
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
