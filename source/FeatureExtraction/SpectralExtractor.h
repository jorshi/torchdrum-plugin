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
    }

    void process(const juce::AudioBuffer<float>& buffer, std::vector<float>& results)
    {
        jassert(buffer.getNumChannels() == 1 && buffer.getNumSamples() == fftSize);

        // Apply window function and copy to FFT buffer
        for (int i = 0; i < fftSize; ++i)
            fftBuffer[i] = buffer.getSample(0, i) * fftWindow[i];

        // Perform FFT
        fft->performFrequencyOnlyForwardTransform(fftBuffer.data());
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
};
