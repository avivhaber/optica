#pragma once
#include "Vec3.h"
#include "Color.h"
#include "Object.h"
#include "Material.h"

class Sphere : public Object {
    public:
        Point center;
        float radius;

        Sphere(Point center = Point(), float radius = 1, Material material = Material());
        Vec3 normalAt(const Point& point) const override;
        Intersection rayIntersection(const Line& ray, Interval tRange = Interval()) const override;
        Point worldToObjectSpace(const Point& point) const override;
        std::pair<double, double> objectToTextureSpace(const Point& point) const override;
        void translate(float x, float y, float z);
};
