#include "Plane.h"
#include "Vec3.h"
#include "cmath"
#include "iostream"

Vec3 Plane::normalAt(const Point& point) const {
    return normal;
}

Color Plane::colorAt(const Point& point) const {
    static Color c1 = Color(1, 1, 0);
    static Color c2 = Color(1, 0, 0);
    float size = 0.2f;
    bool cx = abs(fmod(point.x, 2.0f*size)) < (size);
    bool cz = abs(fmod(point.z, 2.0f*size)) < (size);
    if (cx != cz) return c1;
    return c2;
}

Plane::Plane(Vec3 normal, float D) {
    float len = normal.length();
    this->normal = normal / len;
    this->D = D / len;
}

Intersection Plane::rayIntersection(const Line& ray, Interval tRange) const {
    float ndotd = Vec3::dot(normal, ray.direction);
    if (ndotd == 0.0f) {
        return Intersection(false);
    }

    float t = (D - Vec3::dot(normal, ray.origin)) / ndotd;
    
    if (!tRange.inRangeExclusive(t)) return Intersection(false);
    return Intersection(true, t, ray.at(t));
//    if (ray.direction.y == 0.0f) return Intersection(false);
//    float t = (D - ray.origin.y) / ray.direction.y;
//    if (!tRange.inRangeExclusive(t)) return Intersection(false);
//    return Intersection(true, t, ray.at(t));
}
