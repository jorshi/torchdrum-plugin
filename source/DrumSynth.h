/*
==============================================================================

DrumSynth.h

Simple Drum Synth Class

==============================================================================
*/
#pragma once

#include "DrumSynthParameters.h"
#include "SynthBase.h"
#include "Tonal.h"

class DrumSynth : public SynthWithParameterBase<DrumSynthParameters>
{
public:
    DrumSynth();
    ~DrumSynth() = default;

    // Prepare the synth for playback
    void prepare(double sampleRate, int samplesPerBlock) override;

    // Get the next sample from the synth
    float process() override;

    // Trigger the drum
    void trigger() override;

    // Parameter setters

private:
    Tonal tonal;
};
