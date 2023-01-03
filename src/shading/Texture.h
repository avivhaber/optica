#pragma once
#include <functional>
#include "Color.h"
#include "Line.h"
#include "Vec3.h"

/**
 * A Texture is simply a function that takes in uv coordinates
 * and returns a color. It also takes in the original worldspace
 * point in case the texture wants to do advanced stuff.
 */
using Texture = std::function<Color(double u, double v, const Point& point)>;

namespace Textures {
inline Texture COLOR(const Color& color) {
  return [color](double u, double v, const Point& point) { return color; };
}

inline Texture CHECKERBOARD(const Color& color1, const Color& color2,
                            float squareWidth) {
  return [color1, color2, squareWidth](double u, double v, const Point& point) {
    bool cx = abs(fmod(u, 2.0f * squareWidth)) < (squareWidth);
    cx = u < 0 ? !cx : cx;

    bool cz = abs(fmod(v, 2.0f * squareWidth)) < (squareWidth);
    cz = v < 0 ? !cz : cz;

    if (cx != cz) return color1;
    return color2;
  };
}
}  // namespace Textures
