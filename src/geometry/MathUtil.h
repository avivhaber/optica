#pragma once
#include "Vec3.h"
#include <limits>
#include <random>

namespace Constants {
    inline constexpr float PI {3.1415927};
    inline constexpr float PI_OVER_2 {1.5707964};
    inline constexpr float PI_OVER_180 {PI/180.0f};
    inline constexpr float FLOAT_INF = std::numeric_limits<float>::infinity();
}

namespace MathUtil {
    // Converts degrees to radians.
    inline float toRads(float deg) {
        return deg*Constants::PI_OVER_180;
    }

    // Clips num so that it's between min and max.
    inline float clip(float num, float min, float max) {
        return std::min(max, std::max(min, num));
    }

    // Returns a random float in the range [0,1)
    inline float rand() {
        static std::default_random_engine generator;
        //static std::mt19937 generator;

        static std::uniform_real_distribution<float> distribution(0.0, 1.0);

        return distribution(generator);
    }

    // Returns a random float in the range [min, max)
    inline float rand(float min, float max) {
        return min + rand()*(max - min);
    }
}
