#include "Sphere.h"
#include "Vec3.h"
#include "Line.h"
#include "Object.h"
#include <cmath>
#include <algorithm>
#include <iostream>

Vec3 Sphere::normalAt(const Point& point) const {
    return (point - center)/radius;
}

Sphere::Sphere(Point center, float radius, Color color) : Object(color), center(center), radius(radius) {}

/**
 * Finds the point where the line and sphere intersect.
 * If there's 0 or 1 solutions, the returned point will be invalid (NaN components).
 * If there's 2 solutions, and both t's are positive, the smaller one is returned.
 * If not both positive, the greater t is returned.
*/
Intersection Sphere::rayIntersection(const Line& ray) const {
    Vec3 u = ray.origin - center;
    Vec3 d = ray.direction;
    d.normalize();
    const float& r = radius;

    float udotd = Vec3::dot(u, d);
    float discriminant = udotd*udotd - u.length2() + r*r;

    if (discriminant <= 0) {
        return Intersection(false);
    }

    float sqrtDisc = std::sqrt(discriminant);
    float t1 = -udotd + sqrtDisc;
    float t2 = -udotd - sqrtDisc;

    float t = 0;
    if (t1 > 0 && t2 > 0) {
        t = std::min(t1, t2);
    }
    else {
        t = (std::max(t1, t2)); // in case one of the POIs is at line.origin
    }
    Point poi = ray.at(t);
    return Intersection(true, t, poi, Vec3::distance2(ray.origin, poi));
}

void Sphere::translate(float x, float y, float z) {
    center.x += x;
    center.y += y;
    center.z += z;
}