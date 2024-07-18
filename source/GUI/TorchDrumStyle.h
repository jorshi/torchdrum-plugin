#pragma once

#include "BinaryData.h"
#include "juce_gui_basics/juce_gui_basics.h"

const juce::Colour borderColour = juce::Colour::fromRGB(43, 59, 63);
const juce::Colour innerKnobColourA = juce::Colour::fromRGBA(177, 225, 243, 127);
const juce::Colour innerKnobColourB = juce::Colour::fromRGB(120, 166, 177);
const juce::Colour outerKnobColourA = juce::Colour::fromRGB(126, 142, 147);
const juce::Colour modKnobColourA = juce::Colour::fromRGBA(120, 166, 177, 179);
const juce::Colour modKnobColourB = juce::Colour::fromRGBA(255, 255, 255, 255);
const juce::Colour knobValueBackground = juce::Colour::fromRGBA(249, 247, 243, 153);
const juce::Colour vizualizerGradientColourA = juce::Colour::fromRGB(225, 225, 220);
const juce::Colour vizualizerGradientColourB = juce::Colour::fromRGB(208, 217, 217);

// Spacing based on the original designed size of the dual knob component
const float fullPluginWidth = 960.0f;
const float fullPluginHeight = 550.0f;

const float synthControlComponentX = 583.4984f;
const float synthControlComponentY = 29.1123f;
const float synthControlComponentWidth = 342.3021f;
const float synthControlComponentHeight = 489.6482f;

const float knobRowComponentHeight = 116.235f;
const float knobRowLabelHeight = 23.1006f;
const float knobRowPadding = 8.2488f;

const float dualKnobComponentHeight = 89.2076f;
const float dualKnobComponentWidth = 82.8238f;
const float dualKnobTextBoxHeight = 19.5902f;
const float dualKnobSize = 66.0f;
const float dualKnobPadding =
    dualKnobComponentHeight - (dualKnobTextBoxHeight + dualKnobSize);
const int dualKnobThinStrokeWidth = 1;

const float visualizerComponentX = 218.688f;
const float visualizerComponentY = 56.0911f;
const float visualizerComponentWidth = 330.0f;
const float visualizerComponentHeight = 326.7857f;

const float onsetControlComponentX = 276.9249f;
const float onsetControlComponentY = 416.0552f;
const float onsetControlComponentWidth = 214.1505f;
const float onsetControlComponentHeight = 92.0643f;
const juce::Rectangle<int> onsetControlComponentBounds(276, 416, 214, 92);

const float globalControlComponentX = 56.1953f;
const float globalControlComponentY = 287.9902f;
const float globalControlComponentWidth = 59.3047f;
const float globalControlComponentHeight = 206.8701f;

const float buttonControlComponentX = 28.4389f;
const float buttonControlComponentY = 55.6959f;
const float buttonControlComponentWidth = 113.6449f;
const float buttonControlComponentHeight = 163.343f;

/**
 * Returns FontOption object with the primary typeface for the plugin.
 */
const juce::FontOptions getPluginFont();

/**
 * Returns FontOption object with the bold typeface for the plugin.
 */
const juce::FontOptions getBoldPluginFont();

//==============================================================================
// Functions to calculate the size and position of GUI components for resizing
//==============================================================================

inline float getPluginWidthRatio(float pluginWidth)
{
    return pluginWidth / fullPluginWidth;
}

inline float getSynthControlComponentWidth(float pluginWidth)
{
    return (pluginWidth / fullPluginWidth) * synthControlComponentWidth;
}

inline float getSynthControlComponentX(float pluginWidth)
{
    return (pluginWidth / fullPluginWidth) * synthControlComponentX;
}

inline float getSynthControlComponentY(float pluginHeight)
{
    return (pluginHeight / fullPluginHeight) * synthControlComponentY;
}

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

inline float getDualKnobThinStrokeWidth(float width)
{
    return (width / dualKnobComponentWidth) * dualKnobThinStrokeWidth;
}

inline float getKnobRowComponentHeight(float width)
{
    auto widthRatio = width / synthControlComponentWidth;
    return widthRatio * knobRowComponentHeight;
}

inline float getKnobRowKnobHeight(float height)
{
    return (height / knobRowComponentHeight) * dualKnobComponentHeight;
}

inline float getKnobRowLabelHeight(float height)
{
    return (height / knobRowComponentHeight) * dualKnobTextBoxHeight;
}

inline float getKnobRowPadding(float height)
{
    return (height / knobRowComponentHeight) * knobRowPadding;
}

juce::Rectangle<int> getVisualizerBounds(float pluginWidth);
juce::Rectangle<int> getOnsetControlComponentBounds(float pluginWidth);
juce::Rectangle<int> getGlobalControlComponentBounds(float pluginWidth);
juce::Rectangle<int> getButtonControlComponentBounds(float pluginWidth);
juce::Rectangle<int> getSynthControlComponentBounds(float pluginWidth);

// Dual knob layout relative to bounding box
const juce::Rectangle<int> dualKnobOuterKnobBounds(8, 23, 66, 66);
const juce::Rectangle<int> dualKnobInnerKnobBounds(19, 34, 44, 44);
const juce::Rectangle<int> dualKnobTextBoxBounds(0, 0, 82, 20);
const juce::Rectangle<int> dualKnobTextOutlineLeft(0, 1, 1, 18);
const juce::Rectangle<int> dualKnobTextOutlineRight(81, 1, 1, 18);

// Dual knob single small layout relative to bounding box
const juce::Rectangle<int> singleSmallKnobOuterKnobBounds(5, 46, 46, 46);
const juce::Rectangle<int> singleSmallKnobTextBoxBounds(0, 0, 56, 40);
