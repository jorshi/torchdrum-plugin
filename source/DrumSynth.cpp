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
}

// Prepare the synth for playback
void DrumSynth::prepare(double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(samplesPerBlock);
    juce::ignoreUnused(sampleRate);
}

// Get the next sample from the synth
float DrumSynth::process()
{
    return 0.0f;
}

// Trigger the drum
void DrumSynth::trigger()
{
}
