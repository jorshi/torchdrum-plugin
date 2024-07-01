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
        // Obtain the write lock - this will block until the lock is acquired
        const juce::ScopedWriteLock writeLock(fftLock);

        isPrepared = false;
        sampleRate = sr;
        fftSize = size;

        // Initialize FFT
        int fftOrder = (int) std::log2(fftSize);
        fft = std::make_unique<juce::dsp::FFT>(fftOrder);
        fftBuffer.resize((size_t) fftSize * 2);
        fftWindow.resize((size_t) fftSize);

        // Initialize window function
        juce::dsp::WindowingFunction<float>::fillWindowingTables(
            fftWindow.data(),
            (size_t) fftSize,
            juce::dsp::WindowingFunction<float>::hann,
            false);

        isPrepared = true;
    }

    void process(const juce::AudioBuffer<float>& buffer, std::vector<float>& results)
    {
        jassert(buffer.getNumChannels() == 1 && buffer.getNumSamples() == fftSize);

        // Don't do anything if the FFT is not initialized or updating
        const juce::ScopedTryReadLock readLock(fftLock);
        if (! isPrepared || ! readLock.isLocked())
            return;

        // Apply window function and copy to FFT buffer
        for (size_t i = 0; i < (size_t) fftSize; ++i)
            fftBuffer[i] = buffer.getSample(0, (int) i) * fftWindow[i];

        // Perform FFT
        fft->performFrequencyOnlyForwardTransform(fftBuffer.data(), true);

        // Calculate spectral centroid and flatness
        jassert(results.size() >= 2);
        results[0] = computeSpectralCentroid();
        results[1] = computeSpectralFlatness();
    }

    float computeSpectralCentroid()
    {
        // Calculate spectral centroid based on current frequency magnitude buffer
        float weightedSum = 0.0;
        float norm = 0.0;
        size_t realSize = (size_t) (fftSize / 2) + 1;
        for (size_t n = 0; n < realSize; n++)
        {
            jassert(fftBuffer[n] >= 0.0f);
            weightedSum += n * fftBuffer[n];
            norm += fftBuffer[n];
        }

        if (norm == 0.0)
            return 0.0;

        float centroid = weightedSum / norm;

        // Convert to Hz
        centroid = centroid * (float) sampleRate / fftSize;

        // Convert to semitones
        centroid = 12.0f * std::log2(centroid / 440.0f) + 69.0f;

        return centroid;
    }

    float computeSpectralFlatness()
    {
        float geometricMean = 0.0;
        float arithmeticMean = 0.0;
        size_t realSize = (size_t) (fftSize / 2) + 1;
        for (size_t n = 0; n < realSize; n++)
        {
            float power = std::max(fftBuffer[n] * fftBuffer[n], 1e-10f);
            geometricMean += std::log(power);
            arithmeticMean += power;
        }

        geometricMean /= (float) realSize;
        geometricMean = std::exp(geometricMean);

        arithmeticMean /= (float) realSize;

        float flatness = geometricMean / arithmeticMean;
        flatness = 20.0f * std::log10(flatness);
        return flatness;
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

    juce::ReadWriteLock fftLock;
    std::atomic<bool> isPrepared { false };
};
