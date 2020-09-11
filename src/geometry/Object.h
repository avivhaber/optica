#pragma once
#include "Line.h"
#include "Vec3.h"

// Represents the outcome of an intersection test.
struct Intersection {
    bool hit;
    float t;
    Point poi;

    Intersection(bool hit = false, float t = 0, Point poi = Point()) : hit(hit), t(t), poi(poi) {}
};

// Represents a renderable object in the scene.
// Object is an abstract class that acts as a base for different geometries.
class Object {
    public:
        Color color;
        Object(Color color = Color(1, 1, 1)) : color(color) {}

        virtual Vec3 normalAt(const Point& point) = 0;
        virtual Intersection rayIntersection(const Line& ray) = 0;
};