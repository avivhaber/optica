#pragma once
#include "Color.h"

#include <cmath>

class Renderer {
    public:
        /**
         * The renderer will shoot many randomly perturbed rays for each pixel and then
         * average out the result. This value determines how many samples for each pixel.
         * A higher value will give a sharper and less noisy image, at the cost of an
         * increased render time.
        */ 
        int samplesPerPixel;
        /**
         * Max recursion depth of the ray tracer. A higher value will give more accurate
         * reflections and potentially more accurate shadows, at the cost of increase
         * render time.
        */ 
        int maxDepth;
        /**
         * Used for gamma color correction. colorOut = colorIn ^ (1/gamma).
        */ 
        float gamma {2.0};
        /**
         * Threshold value for detecting if an intersection occured.
         * Ensures that ray originating from object does not intersect with itself.
        */ 
        float tMin {0.0001};
        /**
         * Fraction of light that remains after each reflection.
        */ 
        float reflectance {0.5f};

        Renderer(int spp = 10, int maxDepth = 20);

        Color gammaCorrect(const Color& in) const;
};
