/*
==============================================================================

Snare808.cpp

Implementation of an 808 inspired snare drum synth

==============================================================================
*/

#include "Snare808.h"
#include <juce_audio_basics/juce_audio_basics.h>

Snare808::Snare808()
{
    // Create all the parameter callbacks
    parameters.addCallback(0, [this](float value)
                           { osc1.setFrequencyHz(value); });
    parameters.addCallback(1, [this](float value)
                           { osc1.setModAmount(value); });
    parameters.addCallback(2, [this](float value)
                           { osc2.setFrequencyHz(value); });
    parameters.addCallback(3, [this](float value)
                           { osc2.setModAmount(value); });
    parameters.addCallback(4, [this](float value)
                           { freqEnv.setDecayMs(value); });
    parameters.addCallback(5, [this](float value)
                           { osc1Env.setDecayMs(value); });
    parameters.addCallback(6, [this](float value)
                           { osc2Env.setDecayMs(value); });
    parameters.addCallback(7, [this](float value)
                           { noiseEnv.setDecayMs(value); });
    parameters.addCallback(8, [this](float value)
                           { updateFilterFreq(value); });
    parameters.addCallback(9, [this](float value)
                           { updateFilterQ(value); });
    parameters.addCallback(10, [this](float value)
                           { osc1Gain.setGainDecibels(value); });
    parameters.addCallback(11, [this](float value)
                           { osc2Gain.setGainDecibels(value); });
    parameters.addCallback(12, [this](float value)
                           { noiseGain.setGainDecibels(value); });
    parameters.addCallback(13, [this](float value)
                           { waveshaper.setGainDecibels(value); });
}

// Prepare the synth for playback
void Snare808::prepare(double sr, int samplesPerBlock)
{
    juce::ignoreUnused(samplesPerBlock);
    sampleRate = sr;

    osc1.prepare(sr);
    osc2.prepare(sr);
    osc1Env.prepare(sr);
    osc2Env.prepare(sr);
    freqEnv.prepare(sr);
    noiseEnv.prepare(sr);

    // Initial settings for the noise filter
    noiseFilterSettings.fs = sr;
    noiseFilterSettings.type = Biquad::Type::highpass;
    noiseFilterSettings.peakGainDb = 0.0;
    noiseFilterSettings.q = 0.707;
    noiseFilterSettings.cutoff = 1000.0;
    noiseFilter.setup(noiseFilterSettings);
    noiseFilter.clean();
}

// Get the next sample from the synth
float Snare808::process()
{
    return 0.f;
}

// Trigger the drum
void Snare808::trigger()
{
}

// Update the filter frequency
void Snare808::updateFilterFreq(float value)
{
    float nyquist = 0.5f * sampleRate;
    float freq = std::min(value, nyquist);
    noiseFilter.setFc(freq);
}

// Update the filter Q
void Snare808::updateFilterQ(float value)
{
    noiseFilter.setQ(value);
}
