#pragma once
#include "Line.h"
#include "Vec3.h"
#include "MathUtil.h"
#include "Interval.h"
#include <limits>

class Object;
struct Intersection;

// Represents the outcome of an intersection test.
struct Intersection {
    bool hit; // Whether an intersection occured
    const Object* obj; // The object that was hit. Ensure that obj does not get deleted before this Intersection object.
    float t; // The value of parameter t that corresponds to intersection
    Point point; // The point of intersection

    Intersection(bool hit = false, const Object* obj = nullptr, float t = Constants::FLOAT_INF, Point point = Point())
    : hit(hit), obj(obj), t(t), point(point) {}
};

// Represents a renderable object in the scene.
// Object is an abstract class that acts as a base for different geometries.
class Object {
    public:
        virtual Vec3 normalAt(const Point& point) const = 0;
        virtual Color colorAt(const Point& point) const {return Color(1, 1, 1);}
        virtual Intersection rayIntersection(const Line& ray, Interval tRange = Interval()) const = 0;
};