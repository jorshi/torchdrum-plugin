/**
 * SpectralExtractor.hpp
 * A class for extracting spectral features from a signal.
*/

#pragma once

#include <juce_dsp/juce_dsp.h>

class SpectralExtractor
{
public:
    SpectralExtractor() = default;
    ~SpectralExtractor() = default;

    void prepare(double sr, int fftSize)
    {
        sampleRate = sr;

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

    // Getters
    double getSampleRate() const { return sampleRate; }
    const juce::dsp::FFT& getFFT() const { return *fft; }
    const std::vector<float>& getFFTBuffer() const { return fftBuffer; }
    const std::vector<float>& getFFTWindow() const { return fftWindow; }

private:
    double sampleRate;

    // FFT
    std::unique_ptr<juce::dsp::FFT> fft;
    std::vector<float> fftBuffer;
    std::vector<float> fftWindow;
};
