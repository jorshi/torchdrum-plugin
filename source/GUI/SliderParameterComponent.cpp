#include "SliderParameterComponent.h"

SliderParameterComponent::SliderParameterComponent(juce::RangedAudioParameter* p)
    : parameter(p)
{
    slider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    slider.setNumDecimalPlacesToDisplay(2);

    // Apply the normalisable range to the inner knob
    // Need to convert from float to double
    juce::NormalisableRange<double> range(
        parameter->getNormalisableRange().start,
        parameter->getNormalisableRange().end,
        parameter->getNormalisableRange().interval,
        parameter->getNormalisableRange().skew,
        parameter->getNormalisableRange().symmetricSkew);
    slider.setNormalisableRange(range);

    auto defaultValue = parameter->convertFrom0to1(parameter->getDefaultValue());
    slider.setDoubleClickReturnValue(true, defaultValue);
    slider.setValue(defaultValue);

    addAndMakeVisible(slider);
}

void SliderParameterComponent::paint(juce::Graphics& g) {}

void SliderParameterComponent::resized() { slider.setBounds(getLocalBounds()); }
