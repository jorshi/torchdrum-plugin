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
                           { tonal.setDecay(value); });
    parameters.addCallback(1, [this](float value)
                           { tonal.setTuning(value); });
}

// Prepare the synth for playback
void DrumSynth::prepare(double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(samplesPerBlock);
    tonal.prepare(sampleRate);
}

// Get the next sample from the synth
float DrumSynth::process()
{
    return tonal.process();
}

// Trigger the drum
void DrumSynth::trigger()
{
    tonal.trigger();
}
