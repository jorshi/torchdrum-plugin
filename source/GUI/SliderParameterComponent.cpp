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
    addAndMakeVisible(slider);

    // Parameter listener -- called when the parameter changes from the host
    parameter->addListener(this);

    // Add slider callbacks
    slider.onValueChange = [this] { sliderValueChanged(); };
    slider.onDragStart = [this] { sliderStartedDragging(); };
    slider.onDragEnd = [this] { sliderStoppedDragging(); };

    // Timer callback to check whether the parameter has changed from the host
    startTimer(100);
}

SliderParameterComponent::~SliderParameterComponent()
{
    parameter->removeListener(this);
    stopTimer();
}

void SliderParameterComponent::paint(juce::Graphics& g) {}

void SliderParameterComponent::resized() { slider.setBounds(getLocalBounds()); }

void SliderParameterComponent::parameterValueChanged(int parameterIndex, float newValue)
{
    if (parameterIndex == parameter->getParameterIndex())
        parameterValueHasChanged = 1;
}

void SliderParameterComponent::timerCallback()
{
    bool hasChanged = true;
    if (parameterValueHasChanged.compare_exchange_strong(hasChanged, false))
    {
        if (! isDragging)
        {
            auto newValue = parameter->convertFrom0to1(parameter->getValue());
            slider.setValue(newValue);

            // Speed up the timer interval for smoother updates during parameter changes
            startTimer(50);
        }
    }
    else
    {
        // If the parameter has not changed, then increase the timer interval
        // to reduce CPU usage until the next parameter change
        startTimer(juce::jmin(250, getTimerInterval() + 10));
    }
}

void SliderParameterComponent::sliderValueChanged()
{
    auto newValue = (float) slider.getValue();
    auto currentParameter = parameter->convertFrom0to1(parameter->getValue());
    if (! juce::approximatelyEqual(newValue, currentParameter))
    {
        if (! isDragging)
            parameter->beginChangeGesture();

        auto value = parameter->convertTo0to1(newValue);
        parameter->setValueNotifyingHost(value);

        if (! isDragging)
            parameter->endChangeGesture();
    }
}

void SliderParameterComponent::sliderStartedDragging()
{
    isDragging = true;
    parameter->beginChangeGesture();
}

void SliderParameterComponent::sliderStoppedDragging()
{
    isDragging = false;
    parameter->endChangeGesture();
}
