#pragma once
#include "Line.h"
#include "Vec3.h"
#include "Color.h"
#include "MathUtil.h"
#include "Interval.h"
#include "Intersection.h"
#include "Material.h"
#include <limits>
#include <string>
#include <utility>

struct Intersection;

// Abstract class that represents a renderable object in the scene.
// All geometries inherit from this class and must override its methods.
class Object {
    public:
        Material material;
        // Given a point on the surface of this object, return the outward normal at the point.
        virtual Vec3 normalAt(const Point& point) const = 0;
        // Computes the first intersection between the specified ray and this object.
        virtual Intersection rayIntersection(const Line& ray, Interval tRange = Interval()) const = 0;
        // Transforms coordinate relative to camera (worldspace) to coordinate relative
        // to this object (objectspace). By default, just return the point.
        virtual Point worldToObjectSpace(const Point& point) const {
            return point;
        }
        // Transforms a point in object space to uv coordinates, which correspond to a 2D texture.
        virtual std::pair<double, double> objectToTextureSpace(const Point& point) const = 0;
        // Given a point in worldspace, compute the texture color.
        virtual Color getTextureColor(const Point& point) const {
            double u;
            double v;
            std::tie(u, v) = objectToTextureSpace(worldToObjectSpace(point));
            return material.color;
        }
        Object(Material material = Material()) : material(material) {}
        virtual ~Object() = default;
};
