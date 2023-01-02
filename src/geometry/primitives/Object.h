#pragma once
#include "Line.h"
#include "Vec3.h"
#include "Colors.h"
#include "MathUtil.h"
#include "Interval.h"
#include "Intersection.h"
#include <limits>
#include <string>

struct Intersection;

// Abstract class that represents a renderable object in the scene.
// Different geometries should inherit from this class.
class Object {
    public:
        virtual Vec3 normalAt(const Point& point) const = 0;
        virtual Color colorAt(const Point& point) const {return Color(1, 1, 1);}
        virtual Intersection rayIntersection(const Line& ray, Interval tRange = Interval()) const = 0;
};
