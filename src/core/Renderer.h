#pragma once
#include "Sampler.h"
#include "Colors.h"

#include <cmath>

// Constants and utilty functions for the renderer. The actual path tracer is in scene.h
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
         * Function which generates a random hemispherical direction given an intersection.
        */ 
        const Sampler* sampler;

        Renderer(int spp = 10, int maxDepth = 20, const Sampler* sampler = &Samplers::rejection);

        Color gammaCorrect(const Color& in) const;
};
