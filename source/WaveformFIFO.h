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
    void prepare(double sr, size_t newSize);

    // Fill the buffer with zeros
    void zeroBuffer();

    // Add a sample to the buffer. Once the buffer is full, the contents of the buffer
    // will be copied to a read buffer and the bufferReady flag will be set to true.
    void addSample(float x);

    const std::vector<float>& getReadBuffer() { return readBuffer; }
    const double& getSampleRate() { return sampleRate; }

    bool isBufferReady() { return bufferReady; }
    void markBufferRead() { bufferReady = false; }

private:
    double sampleRate;
    size_t size;
    size_t readIndex;
    size_t writeIndex;
    std::vector<float> fifo;
    std::vector<float> readBuffer;
    std::atomic<bool> bufferReady;
};
