#include "FeatureExtraction.h"

FeatureExtraction::FeatureExtraction()
{
}

void FeatureExtraction::prepare(double sr, int fs, int hs)
{
    sampleRate = sr;
    frameSize = fs;
    hopSize = hs;

    // Prepare spectral extractor
    spectralExtractor.prepare(sr, fs);
    spectralResults.resize(1);
    spectralResults.assign(1, 0.0);
}

void FeatureExtraction::process(const juce::AudioBuffer<float>& buffer, FeatureExtractionResults& results)
{
    jassert(buffer.getNumChannels() == 1 && buffer.getNumSamples() == frameSize);

    // Calculate RMS
    double rms = 0.0;
    auto* audio = buffer.getReadPointer(0);
    for (int i = 0; i < buffer.getNumSamples(); ++i)
    {
        rms += audio[i] * audio[i];
    }

    // Normalize RMS
    rms /= buffer.getNumSamples();
    rms = std::sqrt(rms);

    // Convert to dB with epsilon to avoid log(0) and floor at -80 dB
    rms = 20.0f * std::log10(rms + 1e-8f);
    rms = std::max(rms, -80.0);

    // Update the results
    results.rmsMean.set(rms, true);

    // Calculate spectral centroid
    spectralExtractor.process(buffer, spectralResults);
    results.spectralCentroidMean.set(spectralResults[0], true);
}
