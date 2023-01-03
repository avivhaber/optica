#pragma once
#include "Color.h"
#include "Vec3.h"
#include "Line.h"
#include "Texture.h"
#include <functional>

/**
 * A Sampler is a function that describes how rays bounce off an object.
 * The function takes in the incoming ray, the point of intersection, and
 * the surface normal, and returns the outgoing Ray. Usually the direction
 * of this ray is sampled from some probability distribution.
*/ 
using Sampler = std::function<Line(const Line&, const Point&, const Vec3&)>;

namespace Materials {
    // Ignores the incoming ray, meaning that the material appears roughly equally bright from
    // all angles. Works by sampling a point inside the unit sphere then adding it to the normal.
    // This makes reflections at extreme angles are less likely to occur.
    inline Line DIFFUSE(const Line& incoming, const Point& hit, const Vec3& normal) {
        Vec3 ran;
        while(true) {
            ran = Vec3::randVec(-1, 1);
            if (ran.length2() <= 1) break;
        }
        return Line(hit, normal+ran);
    }

    // Variation of the previous that samples a random point on the unit sphere instead of inside it.
    inline Line DIFFUSE2(const Line& incoming, const Point& hit, const Vec3& normal) {
        Vec3 ran = Vec3::randomUnitVec();
        if (ran.length2() < 1e-8) ran = Vec3(0,0,0);
        return Line(hit, normal+ran);
    }

    // Samples a random point inside the hemisphere at the hit point. Doesn't take into account 
    // the incoming ray or the normal. Looks very unrealistic.
    inline Line NAIVE(const Line& incoming, const Point& hit, const Vec3& normal) {
        Vec3 v = Vec3::randVec(-1, 1);
        if (Vec3::dot(normal, v) < 0) v = -v;
        return Line(hit, v-hit);
    }
}

// Material determines how an object is shaded, indepdendent of its geometry.
class Material {
    public:
        Texture texture;
        Sampler sampleNextRay;
        Material(Color color = Colors::WHITE, Sampler sampler = Materials::DIFFUSE) : texture(Textures::COLOR(color)), sampleNextRay(sampler) {}
        Material(const Texture& texture, Sampler sampler = Materials::DIFFUSE) : texture(texture), sampleNextRay(sampler) {}
};


