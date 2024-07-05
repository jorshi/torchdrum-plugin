#pragma once

#include "BinaryData.h"
#include "juce_gui_basics/juce_gui_basics.h"

const juce::Colour borderColour = juce::Colour::fromRGB(43, 59, 63);
const juce::Colour innerKnobColourA = juce::Colour::fromRGBA(177, 225, 243, 127);
const juce::Colour innerKnobColourB = juce::Colour::fromRGB(120, 166, 177);
const juce::Colour outerKnobColourA = juce::Colour::fromRGB(126, 142, 147);
const juce::Colour modKnobColourA = juce::Colour::fromRGBA(120, 166, 177, 179);
const juce::Colour modKnobColourB = juce::Colour::fromRGBA(255, 255, 255, 255);

// Spacing based on the original designed size of the dual knob component
const float dualKnobComponentHeight = 89.2076f;
const float dualKnobComponentWidth = 82.8238f;
const float dualKnobTextBoxHeight = 19.5902f;
const float dualKnobSize = 66.0f;
const float dualKnobPadding =
    dualKnobComponentHeight - (dualKnobTextBoxHeight + dualKnobSize);

/**
 * Returns FontOption object with the primary typeface for the plugin.
 */
const juce::FontOptions getPluginFont();

inline float getTextHeight(float textBoxHeight)
{
    return (textBoxHeight / 19.19f) * 18.34f;
}

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

inline float getOuterKnobTickLength(float sliderWidth)
{
    return (sliderWidth / 66.0f) * 11.5f;
}

inline float getDualKnobTextBoxHeight(float width)
{
    return (width / dualKnobComponentWidth) * dualKnobTextBoxHeight;
}

inline float getDualKnobPadding(float width)
{
    return (width / dualKnobComponentWidth) * dualKnobPadding;
}
