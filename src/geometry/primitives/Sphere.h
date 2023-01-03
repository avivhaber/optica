#pragma once
#include "Color.h"
#include "Material.h"
#include "Object.h"
#include "Vec3.h"

class Sphere : public Object {
 public:
  Point center;
  float radius;

  Sphere(Point center = Point(), float radius = 1,
         Material material = Material());
  Vec3 normalAt(const Point& point) const override;
  /**
   * Finds the point where the line and sphere intersect.
   * If there's 0 or 1 solutions, the returned point will be invalid (NaN
   * components). If there's 2 solutions, and both t's are positive, the smaller
   * one is returned. If not both positive, the greater t is returned.
   */
  Intersection rayIntersection(const Line& ray,
                               Interval tRange = Interval()) const override;
  Point worldToObjectSpace(const Point& point) const override;
  std::pair<double, double> objectToTextureSpace(
      const Point& point) const override;
  void translate(float x, float y, float z);
};
