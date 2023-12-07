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
        fft = std::make_unique<juce::dsp::FFT>(std::log2(fftSize));
    }

    // Getters
    double getSampleRate() const { return sampleRate; }
    const juce::dsp::FFT& getFFT() const { return *fft; }

private:
    double sampleRate;

    // FFT
    std::unique_ptr<juce::dsp::FFT> fft;
};
