#include "GeometryUtil.h"
#include "Vec3.h"
#include "Line.h"
#include "Sphere.h"
#include <cmath>
#include <limits>
#include <algorithm>

/**
 * Finds the point where the line and sphere intersect.
 * If there's 0 or 1 solutions, the returned point will be invalid (NaN components).
 * If there's 2 solutions, and both t's are positive, the smaller one is returned.
 * If not both positive, the greater t is returned.
*/
Point GeometryUtil::lineSphereIntersection(Line line, Sphere sphere) {
    float fnan = std::numeric_limits<float>::quiet_NaN();

    Vec3 u = line.origin - sphere.center;
    Vec3& d = line.direction;
    float& r = sphere.radius;

    float udotd = Vec3::dot(u, d);
    float discriminant = udotd*udotd - u.length2() + r*r;

    if (discriminant <= 0) {
        return Point (fnan, fnan, fnan);
    }

    float sqrtDisc = std::sqrt(discriminant);
    float t1 = -udotd + sqrtDisc;
    float t2 = -udotd - sqrtDisc;

    if (t1 > 0 && t2 > 0) {
        return line.at(std::min(t1, t2));
    }
    return line.at(std::max(t1, t2));
}