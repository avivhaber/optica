#pragma once
#include "Sampler.h"
#include <cmath>

// Constants and utilty functions for the renderer. The actual path tracer is in scene.h
class Renderer {
    public:
        int spp; // Samples per pixel.
        int maxDepth;
        float albedo;
        float gamma; // Used for gamma correction. colorOut = colorIn ^ (1/gamma).
        const Sampler& sampler; // The function which generates a random hemispherical direction

        Renderer(int spp = 10, int maxDepth = 20, float albedo = 0.5f, float gamma = 2.0f, const Sampler& sampler = SamplerDefaults::rejection)
        : spp(spp), maxDepth(maxDepth), albedo(albedo), gamma(gamma), sampler(sampler) {}

        Color gammaCorrect(const Color& in) const {
            if (gamma == 2.0f) {
                return Color(sqrt(in.x), sqrt(in.y), sqrt(in.z));
            }
            else if (gamma == 3.0f) {
                return Color(cbrt(in.x), cbrt(in.y), cbrt(in.z));
            }
            float exp = 1.0f / gamma;
            return Color(pow(in.x, exp), pow(in.y, exp), pow(in.z, exp));
        }
};
