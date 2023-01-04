#pragma once
#include <functional>
#include "Color.h"
#include "Line.h"
#include "Vec3.h"

/**
 * Function that computes the background color of a Scene. Depends on incoming
 * ray direction. More specifically: Given a ray that does not intersect with
 * any object and will shoot off to the sky, return the Color of this ray.
 */
using BackgroundGenerator = std::function<Color(const Line&)>;

namespace Backgrounds {

// Displays a single color.
inline BackgroundGenerator SIMPLE_COLOR(const Color& color) {
  return [color](const Line& ray) { return color; };
}

// Displays a gradient based off ray's y-value.
inline BackgroundGenerator GRADIENT(const Color& bottom, const Color& top) {
  return [bottom, top](const Line& ray) {
    Vec3 dir = ray.direction.normalize();
    float t = (dir.y + 1.0f) / 2.0f;
    return bottom + ((top - bottom) * t);
  };
}

// Displays a white and light-blue sky. Default background implementation.
inline BackgroundGenerator BLUE_SKY() {
  Color bottom = Colors::WHITE;
  Color top = Colors::SKY_BLUE;
  return GRADIENT(bottom, top);
}
}  // namespace Backgrounds