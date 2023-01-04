#pragma once
#include <cmath>
#include <functional>
#include "Color.h"
#include "Vec3.h"

/**
 * A Texture is simply a function that takes in uv coordinates
 * and returns a color. It can be some kind of pattern generator
 * or a simple image lookup.
 */
using Texture = std::function<Color(double u, double v)>;

namespace Textures {

inline Texture COLOR(const Color& color) {
  return [color](double u, double v) { return color; };
}

inline Texture CHECKERBOARD(const Color& color1, const Color& color2, float squareWidth) {
  return [color1, color2, squareWidth](double u, double v) {
    bool cx = std::abs(std::fmod(u, 2.0f * squareWidth)) < (squareWidth);
    cx = u < 0 ? !cx : cx;

    bool cz = std::abs(std::fmod(v, 2.0f * squareWidth)) < (squareWidth);
    cz = v < 0 ? !cz : cz;

    if (cx != cz) return color1;
    return color2;
  };
}
}  // namespace Textures
