/**
 * Noise.h
*/

#pragma once

#include <cstdlib>

class WhiteNoise
{
public:
    WhiteNoise() = default;
    ~WhiteNoise() = default;

    float process()
    {
        return (float) 2 * rand() / RAND_MAX - 1;
    }
};
