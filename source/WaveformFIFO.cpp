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
