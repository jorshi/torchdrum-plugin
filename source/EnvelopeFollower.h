/**
 * EnvelopeFollower
 * Create an envelope from an input audio signal.
 * Different values for attack and decay can be specified in samples.
 */
#pragma once

class EnvelopeFollower
{
public:
    // Constructor
    EnvelopeFollower() : y0(0.0), up(1.0), down(1.0) {}

    void prepare(float upTimeSamples, float downTimeSamples, float initialValue = 0.0)
    {
        up = 1.0f / upTimeSamples;
        down = 1.0f / downTimeSamples;
        y0 = initialValue;
    }

    float process(float x)
    {
        float y;
        if (x > y0)
        {
            y = y0 + (up * (x - y0));
        }
        else
        {
            y = y0 + (down * (x - y0));
        }
        y0 = y;
        return y;
    }

    // Destructor
    ~EnvelopeFollower() {}

private:
    float y0;
    float up;
    float down;
};