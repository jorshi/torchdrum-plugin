/*
==============================================================================

DrumSynth.cpp

Simple Drum Synth Class

==============================================================================
*/

#include "DrumSynth.h"

DrumSynth::DrumSynth()
{
    // Create all the parameter callbacks
    parameters.addCallback(0, [this](float value)
                           { ampEnv.setDecayMs(value); });
    parameters.addCallback(1, [this](float value)
                           { freqEnv.setDecayMs(value); });
    parameters.addCallback(2, [this](float value)
                           { osc.setFrequencyHz(value); });
    parameters.addCallback(3, [this](float value)
                           { osc.setModAmount(value); });
    parameters.addCallback(4, [this](float value)
                           { waveshaper.setGainDecibels(value); });
    parameters.addCallback(5, [this](float value)
                           { gain.setGainDecibels(value); });
    parameters.addCallback(6, [this](float value)
                           { noiseEnv.setDecayMs(value); });
    parameters.addCallback(7, [this](float value)
                           { noiseGain.setGainDecibels(value); });
}

// Prepare the synth for playback
void DrumSynth::prepare(double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(samplesPerBlock);
    ampEnv.prepare(sampleRate);
    freqEnv.prepare(sampleRate);
    noiseEnv.prepare(sampleRate);
    osc.prepare(sampleRate);
}

// Get the next sample from the synth
float DrumSynth::process()
{
    // Sinusoidal signal
    float y = osc.process(freqEnv.process());
    y = y * ampEnv.process();

    // Noise signal
    float n = noise.process() * noiseEnv.process();
    n = noiseGain.process(n);

    // Combine sinusoidal and noise signals
    y = y + n;

    // Apply waveshaping and gain
    y = waveshaper.process(y);
    y = gain.process(y);

    return y;
}

// Trigger the drum
void DrumSynth::trigger()
{
    ampEnv.trigger();
    freqEnv.trigger();
    noiseEnv.trigger();
}
