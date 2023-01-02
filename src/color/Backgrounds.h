#pragma once
#include "Colors.h"
#include "Vec3.h"
#include "Line.h"
#include <functional>


/**
 * Function that computes the background color of a Scene. Depends on incoming ray direction.
 * More specifically: Given a ray that does not intersect with any object
 * and will shoot off to the sky, return the Color of this ray.
*/ 
using BackgroundGenerator = std::function<Color(const Line&)>;

namespace Backgrounds {
    // Displays a single color.
    inline BackgroundGenerator simpleBackground(const Color& color) {
        return [color](const Line& ray) {
            return color; 
        };
    }

    // Displays a gradient based off ray's y-value.
    inline BackgroundGenerator gradientBackground(const Color& bottom, const Color& top) {
        return [bottom, top](const Line& ray) {
            Vec3 dir = ray.direction.normalize();
            float t = (dir.y + 1.0f) / 2.0f;
            return bottom + ((top - bottom) * t);   
        };
    }

    // Dispays a white and light-blue sky. Default background implementation.
    inline BackgroundGenerator blueSky() {
        Color bottom = Color(1, 1, 1);
        Color top = Color(0.5, 0.7, 1);
        return gradientBackground(bottom, top);
    }
}