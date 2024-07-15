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

    int x = (int) (widthRatio * visualizerX);
    int y = (int) (widthRatio * visualizerY);
    int width = (int) (widthRatio * visualizerWidth);
    int height = (int) (widthRatio * visualizerHeight);

    return juce::Rectangle<int>(x, y, width, height);
}

juce::Rectangle<int> getOnsetControlComponentBounds(float pluginWidth)
{
    auto widthRatio = getPluginWidthRatio(pluginWidth);

    int x = (int) (widthRatio * onsetControlComponentX);
    int y = (int) (widthRatio * onsetControlComponentY);
    int width = (int) (widthRatio * onsetControlComponentWidth);
    int height = (int) (widthRatio * onsetControlComponentHeight);

    return juce::Rectangle<int>(x, y, width, height);
}

juce::Rectangle<int> getGlobalControlComponentBounds(float pluginWidth)
{
    auto widthRatio = getPluginWidthRatio(pluginWidth);

    int x = (int) (widthRatio * globalControlComponentX);
    int y = (int) (widthRatio * globalControlComponentY);
    int width = (int) (widthRatio * globalControlComponentWidth);
    int height = (int) (widthRatio * globalControlComponentHeight);

    return juce::Rectangle<int>(x, y, width, height);
}
