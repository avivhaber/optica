#include "Renderer.h"
#include <cmath>
#include <iostream>
#include "Frame.h"
#include "ImageUtil.h"
#include "Intersection.h"
#include "MathUtil.h"
#include "Scene.h"

Renderer::Renderer(int width, int height, int samplesPerPixel, int maxDepth)
    : camera(Camera(width, height)),
      samplesPerPixel(samplesPerPixel),
      maxDepth(maxDepth) {}

Renderer::Renderer(int width, int height, float fov, float focalLength,
                   int samplesPerPixel, int maxDepth)
    : camera(Camera(width, height, fov, focalLength)),
      samplesPerPixel(samplesPerPixel),
      maxDepth(maxDepth) {}

Renderer::Renderer(const Camera& camera, int samplesPerPixel, int maxDepth)
    : camera(camera), samplesPerPixel(samplesPerPixel), maxDepth(maxDepth) {}

void Renderer::renderKeyFrameAnimation(const Scene& scene, float& property,
                                       float endVal, int numFrames) {
  float delta = (endVal - property) / ((float)numFrames);
  render(scene);
  for (int i = 0; i < numFrames; i++) {
    property += delta;
    render(scene);
  }
}

void Renderer::render(const Scene& scene) {
  Frame f(camera.getImageWidth(), camera.getImageHeight());

  for (int y = 0; y < f.height; y++) {
    for (int x = 0; x < f.width; x++) {
      ColorSet c;
      for (int i = 0; i < samplesPerPixel; i++) {
        Line ray = camera.getCameraRayPertrubed(x, y);
        c.add(traceRay(ray, 1, scene));
      }
      f.buffer[x][y] = gammaCorrect(c.average());
    }
    // Update render progress
    int percentFinished = (100 * (y + 1)) / f.height;
    std::cout << "\rRendering frame " << currentFrame << "..."
              << " (" << percentFinished << "%)" << std::flush;
  }
  ImageUtil::writeImage(f, "render", currentFrame);
  currentFrame++;
  std::cout << std::endl;
}

Color Renderer::traceRay(const Line& ray, int depth, const Scene& scene) const {
  if (depth > maxDepth) return Color(0, 0, 0);

  Intersection closest = getClosestIntersection(ray, scene);
  if (closest.hit) {
    auto obj = scene[closest.objectId];
    Vec3 N = obj->normalAt(closest.point);
    Line nextRay = obj->material.sampleNextRay(ray, closest.point, N);
    return obj->getTextureColor(closest.point) *
           traceRay(nextRay, depth + 1, scene) * reflectance;
  }
  return scene.background(ray);
}

Intersection Renderer::getClosestIntersection(const Line& ray,
                                              const Scene& scene) const {
  Intersection closestHit(false);
  std::string closestId;
  for (auto& entry : scene) {
    std::string currId = entry.first;
    Intersection currHit = entry.second->rayIntersection(ray, hitInterval);
    if (currHit.hit && currHit.t < closestHit.t) {
      closestHit = currHit;
      closestId = currId;
    }
  }
  closestHit.objectId = closestId;
  return closestHit;
}

Color Renderer::gammaCorrect(const Color& in) const {
  if (gamma == 2.0f) {
    return Color(sqrt(in.x), sqrt(in.y), sqrt(in.z));
  } else if (gamma == 3.0f) {
    return Color(cbrt(in.x), cbrt(in.y), cbrt(in.z));
  }
  float exp = 1.0f / gamma;
  return Color(pow(in.x, exp), pow(in.y, exp), pow(in.z, exp));
}
