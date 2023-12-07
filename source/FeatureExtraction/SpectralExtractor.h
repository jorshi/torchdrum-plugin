/**
 * SpectralExtractor.hpp
 * A class for extracting spectral features from a signal.
*/

#pragma once

#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_dsp/juce_dsp.h>

class SpectralExtractor
{
public:
    SpectralExtractor() = default;
    ~SpectralExtractor() = default;

    void prepare(double sr, int size)
    {
        isPrepared = false;
        sampleRate = sr;
        fftSize = size;

        // Initialize FFT
        int fftOrder = std::log2(fftSize);
        fft = std::make_unique<juce::dsp::FFT>(fftOrder);
        fftBuffer.resize(fftSize);
        fftWindow.resize(fftSize);

        // Initialize window function
        juce::dsp::WindowingFunction<float>::fillWindowingTables(
            fftWindow.data(),
            fftSize,
            juce::dsp::WindowingFunction<float>::hann,
            false);

        isPrepared = true;
    }

    void process(const juce::AudioBuffer<float>& buffer, std::vector<float>& results)
    {
        jassert(buffer.getNumChannels() == 1 && buffer.getNumSamples() == fftSize);

        // Don't do anything if the FFT is not initialized
        if (fft == nullptr || ! isPrepared)
            return;

        // Apply window function and copy to FFT buffer
        for (int i = 0; i < fftSize; ++i)
            fftBuffer[i] = buffer.getSample(0, i) * fftWindow[i];

        // Perform FFT
        fft->performFrequencyOnlyForwardTransform(fftBuffer.data());

        // Calculate spectral centroid
        jassert(results.size() >= 1);
        results[0] = computeSpectralCentroid();
    }

    float computeSpectralCentroid()
    {
        // Calculate spectral centroid based on current frequency magnitude buffer
        float weightedSum = 0.0;
        float norm = 0.0;
        int realSize = (fftSize / 2) + 1;
        for (int n = 0; n < realSize; n++)
        {
            jassert(fftBuffer[n] >= 0.0f);
            weightedSum += n * fftBuffer[n];
            norm += fftBuffer[n];
        }

        if (norm == 0.0)
            return 0.0;

        float centroid = weightedSum / norm;

        // Convert to Hz
        centroid = centroid * sampleRate / (float) fftSize;

        // Convert to semitones
        centroid = 12.0f * std::log2(centroid / 440.0f) + 69.0f;

        return centroid;
    }

    // Getters
    double getSampleRate() const { return sampleRate; }
    const juce::dsp::FFT& getFFT() const { return *fft; }
    const std::vector<float>& getFFTBuffer() const { return fftBuffer; }
    const std::vector<float>& getFFTWindow() const { return fftWindow; }

private:
    double sampleRate;
    int fftSize;

    // FFT
    std::unique_ptr<juce::dsp::FFT> fft;
    std::vector<float> fftBuffer;
    std::vector<float> fftWindow;

    std::atomic<bool> isPrepared { false };
};
