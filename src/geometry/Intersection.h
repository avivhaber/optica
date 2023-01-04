#pragma once
#include <string>
#include "MathUtil.h"
#include "Object.h"
#include "Vec3.h"

// Represents the outcome of an ray-object intersection test.
struct Intersection {
  bool hit;              // Whether an intersection occurred
  std::string objectId;  // Unique string identifier of the object that was hit.
  float t;               // The value of the Ray's parameter t at the point of intersection.
  Point point;           // The point of intersection.

  Intersection(bool hit = false, float t = Constants::FLOAT_INF, Point point = Point())
      : hit(hit), t(t), point(point) {}
};
