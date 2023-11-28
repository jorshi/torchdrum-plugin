#include "ExpDecayEnvelope.h"

#include <cmath>
#include <juce_core/juce_core.h>

// Constructor
ExpDecayEnvelope::ExpDecayEnvelope() : sampleRate(44100.0), state(off), currentEnv(0.0) {}

void ExpDecayEnvelope::prepare(double sr)
{
    sampleRate = sr;

    // Linear per-sample update for short attack
    attackSamples = static_cast<int>(0.001 * sampleRate);
    attackRate = 1.0f / (float) attackSamples;

    // Reset the envelope
    currentEnv = 0.0;
    state = off;
}

void ExpDecayEnvelope::trigger()
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

// Exponential time constant approx from:
// https://ccrma.stanford.edu/~jos/pasp/Achieving_Desired_Reverberation_Times.html
void ExpDecayEnvelope::setDecayMs(float newValue)
{
    float samples = newValue * (float) sampleRate * 0.001f;
    rate = 1.0f - (6.91f / samples);
}

float ExpDecayEnvelope::process()
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
        if (currentEnv < 0.0001)
        {
            currentEnv = 0.0;
            state = off;
        }
    }

    return currentEnv;
}
