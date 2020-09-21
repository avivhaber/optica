#pragma once
#include <limits>
#include <random>

namespace Constants {
    constexpr float PI {3.1415927};
    constexpr float PI_OVER_2 {1.5707964};
    constexpr float PI_OVER_180 {PI/180.0f};
    constexpr float FLOAT_INF = std::numeric_limits<float>::infinity();
}

namespace MathUtil {
    inline float toRads(float deg) {
        return deg*Constants::PI_OVER_180;
    }

    inline float clip(float num, float min, float max) {
        return std::min(max, std::max(min, num));
    }

    inline float rand() {
        static std::default_random_engine generator;
        //static std::mt19937 generator;

        static std::uniform_real_distribution<float> distribution(0.0, 1.0);

        return distribution(generator);
    }

    inline float rand(float min, float max) {
        return min + rand()*(max - min);
    }
}
