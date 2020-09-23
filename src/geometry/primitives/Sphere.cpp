#include "Sphere.h"
#include "Vec3.h"
#include "Line.h"
#include "Object.h"
#include "MathUtil.h"
#include <cmath>
#include <algorithm>
#include <iostream>

Vec3 Sphere::normalAt(const Point& point) const {
    return (point - center) / radius;
}

Color Sphere::colorAt(const Point& point) const {
    return color;
}

Sphere::Sphere(Point center, float radius, Color color) : center(center), radius(radius), color(color) {}

/**
 * Finds the point where the line and sphere intersect.
 * If there's 0 or 1 solutions, the returned point will be invalid (NaN components).
 * If there's 2 solutions, and both t's are positive, the smaller one is returned.
 * If not both positive, the greater t is returned.
*/
Intersection Sphere::rayIntersection(const Line& ray, Interval tRange) const {
    Vec3 u = ray.origin - center;
    Vec3 d = ray.direction;
    const float& r = radius;

    float udotd = Vec3::dot(u, d);
    float ddotd = d.length2();
    float discriminant = udotd*udotd - ddotd*(u.length2() - r*r);

    if (discriminant <= 0) {
        return Intersection(false);
    }

    float sqrtDisc = std::sqrt(discriminant);
    float t1 = (-udotd + sqrtDisc) / ddotd;
    float t2 = (-udotd - sqrtDisc) / ddotd;

    float t = 0;
    if (tRange.inRangeExclusive(t2)) {
        t = t2;
    }
    else if (tRange.inRangeExclusive(t1)) {
        t = t1;
    }
    else {
        return Intersection(false);
    }
    Point poi = ray.at(t);
    return Intersection(true, this, t, poi);
}

void Sphere::translate(float x, float y, float z) {
    center.x += x;
    center.y += y;
    center.z += z;
}