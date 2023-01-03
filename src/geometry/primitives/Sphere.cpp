#include "Sphere.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include "Line.h"
#include "Material.h"
#include "MathUtil.h"
#include "Object.h"
#include "Vec3.h"

Vec3 Sphere::normalAt(const Point& point) const {
  return (point - center) / radius;
}

Sphere::Sphere(Point center, float radius, Material material)
    : Object(material), center(center), radius(radius) {}

Intersection Sphere::rayIntersection(const Line& ray, Interval tRange) const {
  Vec3 u = ray.origin - center;
  Vec3 d = ray.direction;
  const float& r = radius;

  float udotd = Vec3::dot(u, d);
  float ddotd = d.length2();
  float discriminant = udotd * udotd - ddotd * (u.length2() - r * r);

  if (discriminant <= 0) {
    return Intersection(false);
  }

  float sqrtDisc = std::sqrt(discriminant);
  float t1 = (-udotd + sqrtDisc) / ddotd;
  float t2 = (-udotd - sqrtDisc) / ddotd;

  float t = 0;
  if (tRange.inRangeExclusive(t2)) {
    t = t2;
  } else if (tRange.inRangeExclusive(t1)) {
    t = t1;
  } else {
    return Intersection(false);
  }
  Point poi = ray.at(t);
  return Intersection(true, t, poi);
}

Point Sphere::worldToObjectSpace(const Point& point) const {
  return point - center;
}

std::pair<double, double> Sphere::objectToTextureSpace(
    const Point& point) const {
  Point p = point.normalize();
  double u = 0.5f + atan2(p.z, p.x) / (2 * Constants::PI);
  double v = 0.5f + asin(p.y) / Constants::PI;
  return std::make_pair(u, v);
}

void Sphere::translate(float x, float y, float z) {
  center.x += x;
  center.y += y;
  center.z += z;
}