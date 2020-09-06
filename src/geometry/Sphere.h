#pragma once
#include "Vec3.h"

class Sphere {
    public:
        Point center;
        float radius;

        Sphere(Point center = Point(0 , 0, 0), float radius = 1) : center(center), radius(radius) {}

        Vec3 normalAt(const Point& point) {
            return (point - center).normalize();
        }
};
