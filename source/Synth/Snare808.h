/*
==============================================================================

DrumSynth.h

Simple Drum Synth Class

==============================================================================
*/
#pragma once

#include "../Biquad.h"
#include "Modules/ExpDecayEnvelope.h"
#include "Modules/Gain.h"
#include "Modules/Noise.h"
#include "Modules/SinusoidalOscillator.h"
#include "Modules/Tanh.h"
#include "Snare808Parameters.h"
#include "SynthBase.h"

class Snare808 : public SynthWithParameterBase<Snare808Parameters>
{
public:
    Snare808();
    ~Snare808() = default;

    // Prepare the synth for playback
    void prepare(double sr, int samplesPerBlock) override;

    // Get the next sample from the synth
    float process() override;

    // Trigger the drum
    void trigger() override;

private:
    double sampleRate = 0.0;

    // Sound sources
    SinusoidalOscillator osc1;
    SinusoidalOscillator osc2;
    WhiteNoise noise;

    // Envelopes
    ExpDecayEnvelope freqEnv;
    ExpDecayEnvelope osc1Env;
    ExpDecayEnvelope osc2Env;
    ExpDecayEnvelope noiseEnv;

    // Filters
    Biquad noiseFilter;
    Biquad::Settings noiseFilterSettings;

    // Mixing and Waveshaping
    Gain osc1Gain;
    Gain osc2Gain;
    Gain noiseGain;
    Tanh waveshaper;

    // Parameter Update Functions
    void updateFilterFreq(float value);
    void updateFilterQ(float value);
};
