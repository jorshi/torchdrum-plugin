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
        return 2.0 * ((float) rand() / (float) RAND_MAX) - 1.0;
    }
};
