#pragma once
#include "Vec3.h"
#include "Object.h"

class Plane : public Object {
    public:
        // Unit length normal
        Vec3 normal;
        // The equation of the plane is given by Ax+By+Cz=D, where normal=(A,B,C)
        float D;

        // Defines the domain of the plane.
        Interval xRange;
        Interval yRange;
        Interval zRange;

        Plane(Vec3 normal, float D, Interval x = Intervals::inf, Interval y = Intervals::inf, Interval z = Intervals::inf);
        Vec3 normalAt(const Point& point) const override;
        Color colorAt(const Point& point) const override;
        Intersection rayIntersection(const Line& ray, Interval tRange = Interval()) const override;
};
