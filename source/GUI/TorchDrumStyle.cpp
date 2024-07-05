#include "TorchDrumStyle.h"

const juce::FontOptions getPluginFont()
{
    auto typeface = juce::Typeface::createSystemTypefaceFor(
        BinaryData::YantramanavMedium_ttf, BinaryData::YantramanavMedium_ttfSize);
    return juce::FontOptions(typeface);
}
