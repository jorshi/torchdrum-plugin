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
