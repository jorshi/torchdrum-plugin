#include "WaveformFIFO.h"
#include <algorithm>
#include <juce_audio_basics/juce_audio_basics.h>

WaveformFIFO::WaveformFIFO() : size(0), readIndex(0), writeIndex(0) {}

void WaveformFIFO::prepare(size_t newSize)
{
    size = newSize;
    readIndex = 0;
    writeIndex = 0;

    buffer.resize(size);
    zeroBuffer();
}

void WaveformFIFO::zeroBuffer() { std::fill(buffer.begin(), buffer.end(), 0.0f); }
