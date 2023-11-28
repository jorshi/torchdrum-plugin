/*
 * Simple Exponential Decay Envelope
 */
#pragma once

class ExpDecayEnvelope
{
public:
    // Constructor
    ExpDecayEnvelope();

    void prepare(double sr);
    float process();
    void trigger();

    // Parameter setter
    void setDecayMs(float newValue);

    // Getters
    float getRate() { return rate; }

    // Destructor
    ~ExpDecayEnvelope() {}

    enum EnvState
    {
        off,
        attack,
        decay
    };

private:
    double sampleRate;

    EnvState state;
    float rate;
    int attackSamples;
    float attackRate;
    float currentEnv;
};
