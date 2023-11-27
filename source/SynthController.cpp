#include "SynthController.h"

SynthController::SynthController()
{
}

void SynthController::prepare(double sr, int samplesPerBlock)
{
    sampleRate = sr;
    juce::ignoreUnused(samplesPerBlock);

    // Initialize the circular audio buffer
    buffer.clear();
    buffer.setSize(1, ONSET_BUFFER_SIZE);

    // Prepate onset detection and state
    onsetDetection.prepare(sampleRate);
    isOnset = false;
    elapsedSamples = 0;
}

void SynthController::process(float x)
{
    addSampleToBuffer(x);

    // If we just triggered, reset the elapsed samples
    bool detected = onsetDetection.process(x);
    if (detected && ! isOnset)
    {
        isOnset = true;
        elapsedSamples = 0;
    }

    // If we are in an onset and we've accumulated enough samples,
    // perform audio feature extraction, calculate synth parameters,
    // and trigger the synth.
    if (isOnset && elapsedSamples++ > ONSET_WINDOW_SIZE)
    {
        isOnset = false;
        featureExtraction.process(buffer, featureExtractionResults);
        // TODO: Extract audio features, calculate synth parameters, and trigger synth
    }
}

void SynthController::addSampleToBuffer(float x)
{
    buffer.setSample(0, currentSample, x);
    currentSample = (currentSample + 1) % buffer.getNumSamples();
    jassert(currentSample < buffer.getNumSamples());
}
