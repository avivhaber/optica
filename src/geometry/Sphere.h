#pragma once
#include "Vec3.h"
#include "Object.h"

class Sphere : public Object {
    public:
        Point center;
        float radius;

        Sphere(Point center = Point(), float radius = 1, Color color = Color(1, 1, 1));
        Vec3 normalAt(const Point& point) const;
        Intersection rayIntersection(const Line& ray) const;

        void translate(float x, float y, float z);
};
