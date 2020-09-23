#pragma once

// Methods of sampling a hemispherical direction
enum class HemiDistribution {
    RejectionUniform,
    CosWeighted,
    Naive
};

class Renderer {
    public:
        int spp; // Samples per pixel.
        float albedo;
        HemiDistribution hemi; // The function which generates a random hemispherical direction

        Renderer(int spp = 10, float albedo = 0.5f, HemiDistribution hemi = HemiDistribution::RejectionUniform);
};