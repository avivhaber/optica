#pragma once
#include "Line.h"
#include "Vec3.h"
#include <limits>

// Represents the outcome of an intersection test.
struct Intersection {
    bool hit; // Whether an intersection occured
    float t; // The value of parameter t that corresponds to intersection
    Point poi; // The point of intersection
    float dist2; // Squared distance from poi to the origin of the intersecting ray.

    Intersection(bool hit = false, float t = 0, Point poi = Point(), float dist2 = std::numeric_limits<float>::infinity())
    : hit(hit), t(t), poi(poi), dist2(dist2) {}
};

// Represents a renderable object in the scene.
// Object is an abstract class that acts as a base for different geometries.
class Object {
    public:
        Color color;
        Object(Color color = Color(1, 1, 1)) : color(color) {}

        virtual Vec3 normalAt(const Point& point) const = 0;
        virtual Intersection rayIntersection(const Line& ray) const = 0;
};