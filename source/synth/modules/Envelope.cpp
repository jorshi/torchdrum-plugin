#include "Envelope.h"

#include <cmath>
#include <juce_core/juce_core.h>

// Constructor
Envelope::Envelope() : sampleRate(44100.0), state(off), currentEnv(0.0) {}

void Envelope::prepare(double sr)
{
    sampleRate = sr;

    // Linear per-sample update for short attack
    attackRate = static_cast<float>(1.0 / (0.001 * sampleRate));
}

void Envelope::trigger()
{
    // If the envelope isn't currently running, then reset
    // to zero
    if (state == off)
    {
        currentEnv = 0.0;
        state = attack;
    }
    else
    {
        state = attack;
    }
}

void Envelope::setDecayRate(float newValue)
{
    // Map to seconds
    newValue = powf(newValue, 2.0);
    float secs = juce::jmap(newValue, 0.0f, 1.0f, 0.01f, 2.0f);
    float samples = secs * (float) sampleRate;

    // Exponential time constant approx from:
    // https://ccrma.stanford.edu/~jos/pasp/Achieving_Desired_Reverberation_Times.html
    rate = 1.0f - (6.91f / samples);
}

float Envelope::process()
{
    if (state == off)
        return 0.0;

    if (state == attack)
    {
        currentEnv += attackRate;
        if (currentEnv >= 1.0)
        {
            currentEnv = 1.0;
            state = decay;
        }
    }
    else if (state == decay)
    {
        currentEnv = currentEnv * rate;
        if (currentEnv < 0.001)
        {
            currentEnv = 0.0;
            state = off;
        }
    }

    return currentEnv;
}
