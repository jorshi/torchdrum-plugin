#include "SynthController.h"

SynthController::SynthController()
{
}

void SynthController::prepare(double sr, int samplesPerBlock)
{
    sampleRate = sr;
    juce::ignoreUnused(samplesPerBlock);

    onsetDetection.prepare(sampleRate);

    // Initialize the circular audio buffer
    buffer.clear();
    buffer.setSize(1, ONSET_BUFFER_SIZE);
}

void SynthController::process(float x)
{
    // Add the input sample to the audio buffer
    buffer.setSample(0, currentSample, x);
    currentSample = (currentSample + 1) % buffer.getNumSamples();
    jassert(currentSample < buffer.getNumSamples());

    // Process the onset detection
    bool trigger = onsetDetection.process(x);
}
