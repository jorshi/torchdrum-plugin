/*
==============================================================================

Snare808.cpp

Implementation of an 808 inspired snare drum synth

==============================================================================
*/

#include "Snare808.h"

Snare808::Snare808()
{
    // Create all the parameter callbacks
    // parameters.addCallback(0, [this](float value)
    //                        { ampEnv.setDecayMs(value); });
    // parameters.addCallback(1, [this](float value)
    //                        { freqEnv.setDecayMs(value); });
    // parameters.addCallback(2, [this](float value)
    //                        { osc.setFrequencyHz(value); });
    // parameters.addCallback(3, [this](float value)
    //                        { osc.setModAmount(value); });
    // parameters.addCallback(4, [this](float value)
    //                        { waveshaper.setGainDecibels(value); });
    // parameters.addCallback(5, [this](float value)
    //                        { gain.setGainDecibels(value); });
    // parameters.addCallback(6, [this](float value)
    //                        { noiseEnv.setDecayMs(value); });
    // parameters.addCallback(7, [this](float value)
    //                        { tonalGain.setGainDecibels(value); });
    // parameters.addCallback(8, [this](float value)
    //                        { noiseGain.setGainDecibels(value); });
}

// Prepare the synth for playback
void Snare808::prepare(double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(samplesPerBlock);
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
