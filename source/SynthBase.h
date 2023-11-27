/*
==============================================================================

SynthBase.h

Base class for drum synthesizers

==============================================================================
*/
#pragma once

#include "SynthParameterBase.h"

class SynthBase
{
public:
    SynthBase() = default;
    ~SynthBase() = default;

    // Prepare the synth for playback
    virtual void prepare(double sampleRate, int samplesPerBlock) = 0;

    // Get the next sample from the synth
    virtual float process() = 0;

    // Trigger the drum
    virtual void trigger() = 0;

    // Get parameters
    virtual SynthParameterBase& getParameters() = 0;
};

// Base class for synthesizers that have parameters, which are derived from
// SynthParameterBase
template <typename Parameters>
class DrumSynthParameterBase : public SynthBase
{
public:
    DrumSynthParameterBase() = default;
    ~DrumSynthParameterBase() = default;

    // Get parameters
    SynthParameterBase& getParameters() override { return parameters; }

protected:
    Parameters parameters;
};
