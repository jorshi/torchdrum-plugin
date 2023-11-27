#include "FeatureExtraction.h"

FeatureExtraction::FeatureExtraction()
{
}

void FeatureExtraction::prepare(double sr)
{
    sampleRate = sr;
}

void FeatureExtraction::process(const juce::AudioBuffer<float>& buffer, FeatureExtractionResults& results)
{
    juce::ignoreUnused(buffer);
    juce::ignoreUnused(results);
}
