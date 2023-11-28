/*
==============================================================================

DrumSynth.h

Simple Drum Synth Class

==============================================================================
*/
#pragma once

#include "DrumSynthParameters.h"
#include "Modules/ExpDecayEnvelope.h"
#include "Modules/Gain.h"
#include "Modules/SinusoidalOscillator.h"
#include "Modules/Tonal.h"
#include "SynthBase.h"

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
    ExpDecayEnvelope ampEnv;
    ExpDecayEnvelope freqEnv;
    SinusoidalOscillator osc;
    Gain gain;
};
