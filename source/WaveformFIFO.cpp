#include "WaveformFIFO.h"
#include <algorithm>
#include <juce_audio_basics/juce_audio_basics.h>

WaveformFIFO::WaveformFIFO() : size(0), readIndex(0), writeIndex(0) {}

void WaveformFIFO::prepare(double sr, size_t newSize)
{
    sampleRate = sr;
    size = newSize;
    readIndex = 0;
    writeIndex = 0;
    bufferReady = false;

    fifo.resize(size);
    readBuffer.resize(size);
    zeroBuffer();

    BiquadCoeff::Settings settings;
    settings.type = BiquadCoeff::lowpass;
    settings.fs = sampleRate;
    settings.cutoff = 10.0;
    settings.q = 0.707;
    settings.peakGainDb = 0.0;
    lowpass.setup(settings);
}

void WaveformFIFO::zeroBuffer()
{
    std::fill(fifo.begin(), fifo.end(), 0.0f);
    std::fill(readBuffer.begin(), readBuffer.end(), 0.0f);
}

void WaveformFIFO::addSample(float x)
{
    if (size == 0)
        return;

    if (writeIndex >= size)
    {
        if (! bufferReady)
        {
            std::copy(fifo.begin(), fifo.end(), readBuffer.begin());
            bufferReady = true;
        }
        writeIndex = 0;
    }

    fifo[writeIndex++] = x;
}

std::pair<float*, size_t> WaveformFIFO::getAtResolutionHz(float resolutionHz)
{
    if (size == 0 || ! bufferReady)
        return std::make_pair(nullptr, 0);

    // Apply lowpass filter to downsample the buffer to the desired resolution
    // Update the lowpass filter cutoff frequency if required
    // Is this necessary?
    // if (! juce::approximatelyEqual((float) lowpass.getFc(), resolutionHz))
    //     lowpass.setFc(resolutionHz);

    // for (size_t i = 0; i < size; ++i)
    //     readBuffer[i] = lowpass.process(readBuffer[i]);

    return std::make_pair(readBuffer.data(), size);
}
