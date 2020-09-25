#pragma once
#include "Line.h"
#include "Vec3.h"

class Sampler {
    public:
        virtual Line sampleNextRay(const Point& hit, const Vec3& normal) const = 0;
};

class RejectionSampler : public Sampler {
    public:
        Line sampleNextRay(const Point& hit, const Vec3& normal) const override {
            Vec3 ran;
            while(true) {
                ran = Vec3::randVec(-1, 1);
                if (ran.length2() <= 1) break;
            }
            return Line(hit, normal+ran);
        }
};

namespace SamplerDefaults {
    constexpr RejectionSampler rejection = RejectionSampler();
}
