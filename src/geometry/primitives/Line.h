#pragma once
#include "Vec3.h"

class Line {
 public:
  Point origin;
  Vec3 direction;

  Line(Point origin = Point(0, 0, 0), Vec3 direction = Vec3(1, 1, 1))
      : origin(origin), direction(direction) {}

  Point at(float t) const { return origin + direction * t; }
};
