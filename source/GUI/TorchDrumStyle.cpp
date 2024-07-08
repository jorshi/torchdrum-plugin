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
