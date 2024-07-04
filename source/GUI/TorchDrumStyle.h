#pragma once

#include "juce_gui_basics/juce_gui_basics.h"

const juce::Colour borderColour = juce::Colour::fromRGB(43, 59, 63);
const juce::Colour innerKnobColourA = juce::Colour::fromRGBA(177, 225, 243, 127);
const juce::Colour innerKnobColourB = juce::Colour::fromRGB(120, 166, 177);
const juce::Colour outerKnobColourA = juce::Colour::fromRGB(126, 142, 147);

inline float getInnerKnobStrokeWidth(float sliderWidth)
{
    return (sliderWidth / 44.5f) * 1.5f;
}

inline float getInnerKnobTickLength(float sliderWidth)
{
    return (sliderWidth / 44.5f) * 14.448f;
}

inline float getOuterKnobStrokeWidth(float sliderWidth)
{
    return (sliderWidth / 66.0f) * 1.5f;
}
