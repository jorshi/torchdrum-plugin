#include "TorchDrumStyle.h"

const juce::FontOptions getPluginFont()
{
    auto typeface = juce::Typeface::createSystemTypefaceFor(
        BinaryData::YantramanavMedium_ttf, BinaryData::YantramanavMedium_ttfSize);
    return juce::FontOptions(typeface);
}

const juce::FontOptions getBoldPluginFont()
{
    auto typeface = juce::Typeface::createSystemTypefaceFor(
        BinaryData::YantramanavBold_ttf, BinaryData::YantramanavBold_ttfSize);
    return juce::FontOptions(typeface);
}

const juce::FontOptions getRegularPluginFont()
{
    auto typeface = juce::Typeface::createSystemTypefaceFor(
        BinaryData::YantramanavRegular_ttf, BinaryData::YantramanavRegular_ttfSize);
    return juce::FontOptions(typeface);
}

juce::Rectangle<int> getVisualizerBounds(float pluginWidth)
{
    auto widthRatio = getPluginWidthRatio(pluginWidth);
    return juce::Rectangle<int>((int) (widthRatio * visualizerComponentX),
                                (int) (widthRatio * visualizerComponentY),
                                (int) (widthRatio * visualizerComponentWidth),
                                (int) (widthRatio * visualizerComponentHeight));
}

juce::Rectangle<int> getOnsetControlComponentBounds(float pluginWidth)
{
    auto widthRatio = getPluginWidthRatio(pluginWidth);
    return juce::Rectangle<int>((int) (widthRatio * onsetControlComponentX),
                                (int) (widthRatio * onsetControlComponentY),
                                (int) (widthRatio * onsetControlComponentWidth),
                                (int) (widthRatio * onsetControlComponentHeight));
}

juce::Rectangle<int> getSynthControlComponentBounds(float pluginWidth)
{
    auto widthRatio = getPluginWidthRatio(pluginWidth);
    return juce::Rectangle<int>((int) (widthRatio * synthControlComponentX),
                                (int) (widthRatio * synthControlComponentY),
                                (int) (widthRatio * synthControlComponentWidth),
                                (int) (widthRatio * synthControlComponentHeight));
}
