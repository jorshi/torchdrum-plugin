#include "OnsetDetection.h"
#include <cmath>

OnsetDetection::OnsetDetection() : sampleRate(44100.0)
{
    // Default internal state
    justTriggered = false;
    debounce = 0;
    prevValue = 0.0f;

    // Default parameters
    onThreshold = 16.0f;
    offThreshold = 4.66f;
    waitSamples = 1000;
    minAmplitude = -55.0f;
}

void OnsetDetection::prepare(double sr)
{
    sampleRate = sr;

    // Setting for fast and slow envelope followers
    fastEnv.prepare(3.0, 383.0, minAmplitude);
    slowEnv.prepare(2205.0, 2205.0, minAmplitude);

    // Setup filter
    BiquadCoeff::Settings settings;
    settings.type = BiquadCoeff::highpass;
    settings.fs = sampleRate;
    settings.cutoff = 600.0;
    settings.q = 0.707;
    settings.peakGainDb = 0.0;

    hipass.setup(settings);
    hipass.clean();

    // Reset internal state variables
    justTriggered = false;
    debounce = 0;
    prevValue = 0.0f;
}

bool OnsetDetection::process(float x)
{
    float diff = onsetSignal(x);
    if (diff >= onThreshold && ! justTriggered && prevValue < onThreshold && debounce == 0)
    {
        justTriggered = true;
        debounce = waitSamples;
        return true;
    }
    else if (debounce > 0)
    {
        debounce = debounce - 1;
    }

    if (justTriggered && diff < offThreshold)
    {
        justTriggered = false;
    }

    prevValue = diff;
    return false;
}

float OnsetDetection::onsetSignal(float x)
{
    // Apply highpass filter
    x = static_cast<float>(hipass.process(x));

    // Rectify, convert to dB, and set minimum value
    x = std::abs(x);
    x = 20.0f * log10f(x);
    x = std::fmax(x, minAmplitude);

    // Apply envelope followers
    float fast = fastEnv.process(x);
    float slow = slowEnv.process(x);
    float diff = fast - slow;

    return diff;
}

void OnsetDetection::updateParameters(float onThresh, float offThresh, int wait)
{
    onThreshold = onThresh;
    offThreshold = offThresh;
    waitSamples = wait;
}
