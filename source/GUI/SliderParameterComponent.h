#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include <shared_plugin_helpers/shared_plugin_helpers.h>

class SliderParameterComponent : public juce::Component,
                                 private juce::AudioProcessorParameter::Listener,
                                 private juce::Timer
{
public:
    SliderParameterComponent() = delete;
    SliderParameterComponent(juce::RangedAudioParameter* p);
    ~SliderParameterComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

    juce::Slider& getSlider() { return slider; }

    // Parameter listener
    void parameterValueChanged(int parameterIndex, float newValue) override;
    void parameterGestureChanged(int parameterIndex, bool gestureIsStarting) override {}

    // Timer callback
    void timerCallback() override;

private:
    void sliderValueChanged();
    void sliderStartedDragging();
    void sliderStoppedDragging();

    juce::RangedAudioParameter* parameter;
    juce::Slider slider;
    bool isDragging = false;
    std::atomic<bool> parameterValueHasChanged = false;
};
