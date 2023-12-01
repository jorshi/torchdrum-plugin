/**
 * FeatureValue.h
 *
 * A class to hold a single feature value and support normalization.
*/

#pragma once

#include <juce_core/juce_core.h>
#include <limits>

template <typename T>
class FeatureValue
{
public:
    FeatureValue() = default;
    ~FeatureValue() = default;

    // Set the value
    void set(T newValue, bool updateMinMax = false)
    {
        value = newValue;
        if (updateMinMax)
        {
            if (value < minValue)
                minValue = value;

            if (value > maxValue)
                maxValue = value;
        }
    }

    // Set min and max values
    void setMinMax(T newMinValue, T newMaxValue)
    {
        minValue = newMinValue;
        maxValue = newMaxValue;
    }

    // Get the raw value
    T getRawValue() const { return value; }

    // Get the normalized value
    T getNormalized() const
    {
        if (minValue == maxValue || minValue == std::numeric_limits<T>::max())
            return 0.5;

        T normalized = (value - minValue) / (maxValue - minValue);
        return juce::jlimit(static_cast<T>(0.0), static_cast<T>(1.0), normalized);
    }

    // Get the minmax values
    std::pair<T, T> getMinMax() const { return std::make_pair(minValue, maxValue); }

    // Reset the min and max values
    void reset()
    {
        minValue = std::numeric_limits<T>::max();
        maxValue = std::numeric_limits<T>::lowest();
    }

private:
    T value;
    T minValue = std::numeric_limits<T>::max();
    T maxValue = std::numeric_limits<T>::lowest();
};
