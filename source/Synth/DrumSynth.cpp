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
    // parameters.addCallback(0, [this](float value)
    //                        { tonal.setDecay(value); });
    // parameters.addCallback(1, [this](float value)
    //                        { tonal.setTuning(value); });
}

// Prepare the synth for playback
void DrumSynth::prepare(double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(samplesPerBlock);
    tonal.prepare(sampleRate);

    ampEnv.prepare(sampleRate);
    freqEnv.prepare(sampleRate);
    osc.prepare(sampleRate);
}

// Get the next sample from the synth
float DrumSynth::process()
{
    float y = osc.process(freqEnv.process());
    float amp = ampEnv.process();
    return y * amp;
}

// Trigger the drum
void DrumSynth::trigger()
{
    ampEnv.trigger();
    freqEnv.trigger();
    tonal.trigger();
}
