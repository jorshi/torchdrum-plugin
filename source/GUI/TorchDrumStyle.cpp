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

juce::Rectangle<int> getVisualizerBounds(float pluginWidth)
{
    auto widthRatio = getPluginWidthRatio(pluginWidth);
    return juce::Rectangle<int>((int) (widthRatio * visualizerX),
                                (int) (widthRatio * visualizerY),
                                (int) (widthRatio * visualizerWidth),
                                (int) (widthRatio * visualizerHeight));
}

juce::Rectangle<int> getOnsetControlComponentBounds(float pluginWidth)
{
    auto widthRatio = getPluginWidthRatio(pluginWidth);
    return juce::Rectangle<int>((int) (widthRatio * onsetControlComponentX),
                                (int) (widthRatio * onsetControlComponentY),
                                (int) (widthRatio * onsetControlComponentWidth),
                                (int) (widthRatio * onsetControlComponentHeight));
}

juce::Rectangle<int> getGlobalControlComponentBounds(float pluginWidth)
{
    auto widthRatio = getPluginWidthRatio(pluginWidth);
    return juce::Rectangle<int>((int) (widthRatio * globalControlComponentX),
                                (int) (widthRatio * globalControlComponentY),
                                (int) (widthRatio * globalControlComponentWidth),
                                (int) (widthRatio * globalControlComponentHeight));
}

juce::Rectangle<int> getButtonControlComponentBounds(float pluginWidth)
{
    auto widthRatio = getPluginWidthRatio(pluginWidth);
    return juce::Rectangle<int>((int) (widthRatio * buttonControlComponentX),
                                (int) (widthRatio * buttonControlComponentY),
                                (int) (widthRatio * buttonControlComponentWidth),
                                (int) (widthRatio * buttonControlComponentHeight));
}
