#pragma once
#include "Vec3.h"

class Sphere {
    public:
        Point center;
        float radius;
        Color color;

        Sphere(
            Point center = Point(0 , 0, 0),
            float radius = 1,
            Color color = Color(1, 1, 1)
        ) : center(center), radius(radius), color(color) {}

        Vec3 normalAt(const Point& point) {
            return (point - center).normalize();
        }
};
