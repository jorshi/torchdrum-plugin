/**
 * FIFO buffer for passing buffers of data between threads.
 * Expected that the audio thread will write to the buffer, and the GUI thread will
 * read from the buffer.
 */

#pragma once

#include <vector>

class WaveformFIFO
{
public:
    WaveformFIFO();
    ~WaveformFIFO() = default;

    // Initialize the buffer to the given size
    void prepare(size_t newSize);

    // Fill the buffer with zeros
    void zeroBuffer();

    void addSample(float x)
    {
        if (size == 0)
            return;

        buffer[writeIndex] = x;
        writeIndex = (writeIndex + 1) % size;
    }

private:
    size_t size;
    size_t readIndex;
    size_t writeIndex;
    std::vector<float> buffer;
};
