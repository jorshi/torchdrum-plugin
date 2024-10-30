#pragma once

#include "BinaryData.h"
#include "KnobLookAndFeel.h"
#include "SliderParameterComponent.h"
#include "TorchDrumStyle.h"
#include "juce_gui_basics/juce_gui_basics.h"
#include <shared_plugin_helpers/shared_plugin_helpers.h>

class DualKnobComponent : public juce::Component, juce::Slider::Listener
{
public:
    enum class KnobType
    {
        Dual,
        SingleSmall,
        SingleLarge
    };

    DualKnobComponent() = delete;
    DualKnobComponent(juce::RangedAudioParameter* p,
                      juce::NormalisableRange<double> range,
                      KnobType knobType = KnobType::Dual);

    void setLayout(KnobType knobType);
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
    void setTextBoxBorderSize(juce::BorderSize<int> newBorderSize);
    void setModulatedValue(float newValue);

private:
    // Parameter
    juce::RangedAudioParameter* parameter;
    juce::NormalisableRange<double> range;

    InnerKnobLookAndFeel innerKnobLookAndFeel;
    OuterKnobLookAndFeel outerKnobLookAndFeel;
    SliderParameterComponent innerKnob;
    juce::Slider outerKnob;
    juce::Label textBox;
    juce::Label valueBox;
    juce::FontOptions fontOptions;

    // Layout
    juce::Rectangle<int> leftTextBoxLine;
    juce::Rectangle<int> rightTextBoxLine;

    std::atomic<bool> mouseOver = false;
    std::atomic<bool> dragging = false;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DualKnobComponent)
};
