/**
 * FeatureExtraction.h
 * Performs audio feature extraction on an input buffer
 *
 * TODO: Implement feature extraction based on Rodrigo Constanzo's SP-Tools
 * - RMS Loudness (should this include the perceptual filtering?)
 * - Spectral Centroid
 * - Spectral Flatness
 * - Pitch?
 *
 * These should be calculated on a per-frame basis and then take the mean and first
 * order difference (mean of?).
 * Spectal features can all be calculated within a single class that uses the built-in
 * JUCE FFT class.
 * Pre-calculate a window function for the FFT. So we should know the window size and
 * hop size at time of initialization.
 *
 * Implement the feature normalizers -- maybe this is a separate class that holds the
 * min and max values for each feature and then normalizes the input feature to a
 * range of 0 to 1. This could have a method to perform a rolling normalization, where
 * the min and max values are updated over time. (This should be able to be frozen and
 * also reset).
**/

#pragma once

#include "FeatureValue.h"
#include "SpectralExtractor.h"
#include <juce_audio_utils/juce_audio_utils.h>

struct FeatureExtractionResults
{
    FeatureValue<float> rmsMean;
    FeatureValue<float> spectralCentroidMean;
    FeatureValue<float> spectralFlatnessMean;

    void reset()
    {
        rmsMean.reset();
        spectralCentroidMean.reset();
        spectralFlatnessMean.reset();
    }
};

class FeatureExtraction
{
public:
    FeatureExtraction();
    ~FeatureExtraction() {}

    // Prepare the feature extraction with sample rate
    void prepare(double sr, int frameSize, int hopSize);

    // Process a buffer of audio samples and store the results
    void process(const juce::AudioBuffer<float>& buffer, FeatureExtractionResults& results);

    // Getters
    double getSampleRate() const { return sampleRate; }
    int getFrameSize() const { return frameSize; }
    int getHopSize() const { return hopSize; }

private:
    double sampleRate;
    int frameSize;
    int hopSize;

    // Spectral features
    SpectralExtractor spectralExtractor;
    std::vector<float> spectralResults;
};
