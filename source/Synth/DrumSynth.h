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
#include "Modules/Noise.h"
#include "Modules/SinusoidalOscillator.h"
#include "Modules/Tanh.h"
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

private:
    ExpDecayEnvelope ampEnv;
    ExpDecayEnvelope freqEnv;
    ExpDecayEnvelope noiseEnv;

    SinusoidalOscillator osc;
    WhiteNoise noise;

    Tanh waveshaper;
    Gain noiseGain;
    Gain gain;
};
