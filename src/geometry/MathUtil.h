#pragma once
#include <limits>

namespace Constants {
    constexpr float PI {3.1415927};
    constexpr float PI_OVER_2 {1.5707964};
    constexpr float PI_OVER_180 {PI/180.0f};
    constexpr float FLOAT_INF = std::numeric_limits<float>::infinity();
}

namespace MathUtil {
    inline bool inRangeExclusive(float val, float min, float max) {
        return (val > min && val < max);
    }
    inline float toRads(float deg) {
        return deg*Constants::PI_OVER_180;
    }
}
