#pragma once
#include "Line.h"
#include "Vec3.h"

class Sampler {
    public:
        virtual Line sampleNextRay(const Point& hit, const Vec3& normal) const = 0;
};

// Samples a random point inside the unit sphere relative to the normal. Weighted towards the normal,
// ie. reflections at extreme angles are less likely to occur.
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

// Samples a random point ON the unit sphere relative to the normal. Truly uniform.
class LambertianSampler : public Sampler {
    public:
        Line sampleNextRay(const Point& hit, const Vec3& normal) const override {
            Vec3 ran;
            while(true) {
                ran = Vec3::randomUnitVec();
                if (ran.length2() <= 1) break;
            }
            return Line(hit, normal+ran);
        }
};

// Samples a random point inside the hemisphere at the hit point.
// Doesn't take into account the normal.
class NaiveSampler : public Sampler {
    public:
        Line sampleNextRay(const Point& hit, const Vec3& normal) const override {
            Vec3 v = Vec3::randVec(-1, 1);
            if (Vec3::dot(normal, v) < 0) v = -v;
            return Line(hit, v-hit);
        }
};

namespace Samplers {
    inline constexpr RejectionSampler rejection = RejectionSampler();
    inline constexpr LambertianSampler lambert = LambertianSampler();
    inline constexpr NaiveSampler naive = NaiveSampler();
}
