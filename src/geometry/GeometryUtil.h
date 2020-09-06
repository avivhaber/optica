#pragma once
#include "Vec3.h"
#include "Line.h"
#include "Sphere.h"

namespace constants {
    constexpr float PI {3.1415927};
    constexpr float PI_OVER_2 {1.5707964};
}

namespace GeometryUtil {
    Point LineSphereIntersection(Line line, Sphere sphere);
}