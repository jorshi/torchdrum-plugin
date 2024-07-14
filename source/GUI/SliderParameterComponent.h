#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include <shared_plugin_helpers/shared_plugin_helpers.h>

class SliderParameterComponent : public juce::Component
{
public:
    SliderParameterComponent() = delete;
    SliderParameterComponent(juce::RangedAudioParameter* p);

    void paint(juce::Graphics& g) override;
    void resized() override;

    juce::Slider& getSlider() { return slider; }

private:
    void sliderValueChanged();
    void sliderStartedDragging();
    void sliderStoppedDragging();

    juce::RangedAudioParameter* parameter;
    juce::Slider slider;
    bool isDragging = false;
};
