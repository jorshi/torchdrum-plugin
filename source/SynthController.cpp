#include "SynthController.h"

SynthController::SynthController()
{
}

void SynthController::prepare(double sr, int samplesPerBlock)
{
    sampleRate = sr;
    juce::ignoreUnused(samplesPerBlock);

    onsetDetection.prepare(sampleRate);
}

void SynthController::process(float x)
{
    bool trigger = onsetDetection.process(x);
}
