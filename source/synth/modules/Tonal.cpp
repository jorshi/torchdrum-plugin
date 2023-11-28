#include "Tonal.h"
#include <cmath>
#include <juce_core/juce_core.h>

// Constructor
Tonal::Tonal() : sampleRate(44100), tuning(100.0), phase(0.0), phaseIncr(0.0) {}

void Tonal::prepare(double rate)
{
    pitchEnvelope.prepare(rate);
    ampEnvelope.prepare(rate);

    sampleRate = rate;
}

float Tonal::process()
{
    float y = sin(phase);
    float pitchAmount = pitchEnvelope.process() * 4.0f + 1.0f;
    phase += phaseIncr * pitchAmount;
    if (phase >= 2 * M_PI)
        phase = phase - 2.0f * (float) M_PI;

    return y * ampEnvelope.process();
}

void Tonal::trigger()
{
    pitchEnvelope.trigger();
    ampEnvelope.trigger();
}

// Parameter settters
void Tonal::setDecay(float newValue)
{
    pitchEnvelope.setDecayRate(newValue * 0.3f);
    ampEnvelope.setDecayRate(newValue * 0.9f);
}

void Tonal::setTuning(float newValue)
{
    newValue = powf(newValue, 2.0f);
    tuning = juce::jmap(newValue, 0.0f, 1.0f, 20.0f, 400.0f);
    phaseIncr = static_cast<float>(2.0 * M_PI * tuning / sampleRate);
}
