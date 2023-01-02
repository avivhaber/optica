#include "Renderer.h"
#include <cmath>

Color Renderer::gammaCorrect(const Color& in) const {
    if (gamma == 2.0f) {
        return Color(sqrt(in.x), sqrt(in.y), sqrt(in.z));
    }
    else if (gamma == 3.0f) {
        return Color(cbrt(in.x), cbrt(in.y), cbrt(in.z));
    }
    float exp = 1.0f / gamma;
    return Color(pow(in.x, exp), pow(in.y, exp), pow(in.z, exp));
}

Renderer::Renderer(int spp, int maxDepth, const Sampler* sampler)
: spp(spp), maxDepth(maxDepth), sampler(sampler) {
    this->sampler = sampler;
}
