#include "Plane.h"
#include "Vec3.h"
#include "cmath"
#include "iostream"

Vec3 Plane::normalAt(const Point& point) const { return normal; }

Plane::Plane(Vec3 normal, float D, Interval x, Interval y, Interval z,
             Material material)
    : Object(material), xRange(x), yRange(y), zRange(z) {
  float len = normal.length();
  this->normal = normal / len;
  this->D = D / len;
}

Intersection Plane::rayIntersection(const Line& ray, Interval tRange) const {
  float ndotd = Vec3::dot(normal, ray.direction);
  if (ndotd == 0.0f) {
    return Intersection(false);
  }

  float t = (D - Vec3::dot(normal, ray.origin)) / ndotd;

  if (!tRange.inRangeExclusive(t)) return Intersection(false);

  Vec3 p = ray.at(t);
  if (!xRange.inRangeExclusive(p.x) || !yRange.inRangeExclusive(p.y) ||
      !zRange.inRangeExclusive(p.z)) {
    return Intersection(false);
  }

  return Intersection(true, t, p);
}

Point Plane::worldToObjectSpace(const Point& point) const {
  // Create orthogonal basis vectors of plane
  Vec3 b1 = Vec3::cross(normal, Vec3(1, 0, 0)).normalize();
  if (b1 == Vec3(0, 0, 0)) {
    b1 = Vec3::cross(normal, Vec3(0, 0, 1)).normalize();
  }
  Vec3 b2 = Vec3::cross(normal, b1).normalize();

  // Project point onto bases.
  float x = Vec3::dot(b1, point);
  float y = Vec3::dot(b2, point);
  return Point(x, y, 0);
}

std::pair<double, double> Plane::objectToTextureSpace(
    const Point& point) const {
  // TODO: Fix texture scaling for planes
  return std::make_pair(point.x, point.y);
}
