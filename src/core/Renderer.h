#pragma once
#include "Sampler.h"
#include "Colors.h"

#include <cmath>

// Constants and utilty functions for the renderer. The actual path tracer is in scene.h
class Renderer {
    public:
        int spp; // Samples per pixel.
        int maxDepth;
        float albedo {0.5};
        float gamma {2.0}; // Used for gamma correction. colorOut = colorIn ^ (1/gamma).
        float tMin {0.0001};
        const Sampler* sampler; // The function which generates a random hemispherical direction

        Renderer(int spp = 10, int maxDepth = 20, const Sampler* sampler = &Samplers::rejection);

        Color gammaCorrect(const Color& in) const;
};
