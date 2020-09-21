#pragma once
#include "Line.h"
#include "Vec3.h"
#include "MathUtil.h"
#include "Interval.h"
#include <limits>

// Represents the outcome of an intersection test.
struct Intersection {
    bool hit; // Whether an intersection occured
    float t; // The value of parameter t that corresponds to intersection
    Point poi; // The point of intersection

    Intersection(bool hit = false, float t = Constants::FLOAT_INF, Point poi = Point())
    : hit(hit), t(t), poi(poi) {}
};

// Represents a renderable object in the scene.
// Object is an abstract class that acts as a base for different geometries.
class Object {
    public:
        virtual Vec3 normalAt(const Point& point) const = 0;
        virtual Color colorAt(const Point& point) const {return Color(1, 1, 1);}
        virtual Intersection rayIntersection(const Line& ray, Interval tRange = Interval()) const = 0;
};