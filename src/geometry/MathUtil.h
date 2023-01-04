#pragma once
#include <algorithm>
#include <limits>
#include <random>
#include "Vec3.h"

namespace Constants {
inline constexpr float PI{3.14159265359};
inline constexpr float PI_OVER_2{PI / 2};
inline constexpr float ONE_OVER_PI{1.0f / PI};
inline constexpr float PI_OVER_180{PI / 180.0f};
inline constexpr float FLOAT_INF = std::numeric_limits<float>::infinity();
}  // namespace Constants

namespace MathUtil {
// Converts degrees to radians.
inline float toRads(float deg) { return deg * Constants::PI_OVER_180; }

// Clips num so that it's between min and max.
inline float clip(float num, float min, float max) { return std::min(max, std::max(min, num)); }

// Linearly interpolate between x0 and x1 according to parameter t.
inline double lerp(double x0, double x1, double t) { return (1 - t) * x0 + t * x1; }

// Returns a random float in the range [0,1)
inline float rand() {
  static std::default_random_engine generator;
  // static std::mt19937 generator;

  static std::uniform_real_distribution<float> distribution(0.0, 1.0);

  return distribution(generator);
}

// Returns a random float in the range [min, max)
inline float rand(float min, float max) { return min + rand() * (max - min); }
}  // namespace MathUtil
