#pragma once
#include <functional>
#include "Color.h"
#include "Line.h"
#include "Texture.h"
#include "Vec3.h"

/**
 * A Sampler is a function that describes how rays bounce off an object.
 * The function takes in the incoming ray, the point of intersection, and
 * the surface normal, and returns the outgoing Ray. Usually the direction
 * of this ray is sampled from some probability distribution.
 */
using Sampler = std::function<Line(const Line&, const Point&, const Vec3&)>;

namespace Materials {

// Ignores the incoming ray, meaning that the material appears roughly equally
// bright from all angles. Works by sampling a point inside the unit sphere then
// adding it to the normal. This makes reflections at extreme angles less
// likely to occur.
inline Line DIFFUSE(const Line& incoming, const Point& hit, const Vec3& normal) {
  Vec3 ran;
  while (true) {
    ran = Vec3::randVec(-1, 1);
    if (ran.length2() <= 1) break;
  }
  return Line(hit, normal + ran);
}

// Variation of the previous that samples a random point on the unit sphere
// instead of inside it. Results in a slightly brighter look, but is technically
// more true-to-life.
inline Line DIFFUSE2(const Line& incoming, const Point& hit, const Vec3& normal) {
  Vec3 ran = Vec3::randomUnitVec();
  if (ran.nearZero()) ran = Vec3(0, 0, 0);
  return Line(hit, normal + ran);
}

// Perfectly reflective mirror material. Angle of incidence == Angle of reflection.
inline Line MIRROR(const Line& incoming, const Point& hit, const Vec3& normal) {
  Vec3 reflected = incoming.direction - normal * (2 * Vec3::dot(incoming.direction, normal));
  return Line(hit, reflected);
}

// Like the normal mirror, but with some perturbation.
// A fuzziness value that's too high may cause visual bugs.
inline Sampler FUZZY_MIRROR(float fuzziness) {
  return [fuzziness](const Line& incoming, const Point& hit, const Vec3& normal) {
    Vec3 reflected = incoming.direction - normal * (2 * Vec3::dot(incoming.direction, normal));
    reflected += Vec3::randomUnitVec() * fuzziness;
    return Line(hit, reflected);
  };
}

// Samples a random point inside the hemisphere centred at the hit point. Doesn't take
// into account the incoming ray or the normal. Looks very unrealistic.
inline Line NAIVE(const Line& incoming, const Point& hit, const Vec3& normal) {
  Vec3 v = Vec3::randVec(-1, 1);
  if (Vec3::dot(normal, v) < 0) v = -v;
  return Line(hit, v - hit);
}
}  // namespace Materials

// Material determines how an object is shaded.
class Material {
 public:
  Texture texture;
  Sampler sampleNextRay;
  Material(Color color = Colors::WHITE, Sampler sampler = Materials::DIFFUSE)
      : texture(Textures::COLOR(color)), sampleNextRay(sampler) {}
  Material(const Texture& texture, Sampler sampler = Materials::DIFFUSE)
      : texture(texture), sampleNextRay(sampler) {}
};
