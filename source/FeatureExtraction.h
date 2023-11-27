/**
 * FeatureExtraction.h
 * Performs audio feature extraction on an input buffer
**/

#pragma once

#include <juce_audio_utils/juce_audio_utils.h>

struct FeatureExtractionResults
{
    double rmsMean;
    double rmsDiff;
};

class FeatureExtraction
{
public:
    FeatureExtraction();
    ~FeatureExtraction() {}

    // Prepare the feature extraction with sample rate
    void prepare(double sr);

    // Process a buffer of audio samples and store the results
    void process(const juce::AudioBuffer<float>& buffer, FeatureExtractionResults& results);

private:
    double sampleRate;
};
