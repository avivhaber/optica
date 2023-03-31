#include "Renderer.h"
#include <cmath>
#include <iostream>
#include <thread>
#include "Frame.h"
#include "ImageUtil.h"
#include "Intersection.h"
#include "MathUtil.h"
#include "Scene.h"

using namespace std::placeholders;

Renderer::Renderer(int width, int height, int samplesPerPixel, int maxDepth)
    : camera(Camera(width, height)), samplesPerPixel(samplesPerPixel), maxDepth(maxDepth) {}

Renderer::Renderer(int width, int height, float fov, float focalLength, int samplesPerPixel,
                   int maxDepth)
    : camera(Camera(width, height, fov, focalLength)),
      samplesPerPixel(samplesPerPixel),
      maxDepth(maxDepth) {}

Renderer::Renderer(const Camera& camera, int samplesPerPixel, int maxDepth)
    : camera(camera), samplesPerPixel(samplesPerPixel), maxDepth(maxDepth) {}

void Renderer::renderKeyFrameAnimation(const Scene& scene, float& property, float endVal,
                                       int numFrames) {
  float delta = (endVal - property) / ((float)numFrames);
  render(scene);
  for (int i = 0; i < numFrames; i++) {
    property += delta;
    render(scene);
  }
}

void Renderer::render(const Scene& scene, bool multithreading) {
  Frame f(camera.getImageWidth(), camera.getImageHeight());

  int numThreads = multithreading ? std::thread::hardware_concurrency() : 1;
  numThreads = std::max(numThreads, 1);
  std::atomic<int> currPixel(f.width * f.height - 1);
  std::vector<std::thread> threads;
  for (int i = 0; i < numThreads; i++) {
    threads.emplace_back(std::bind(&Renderer::renderingWorker, this, _1, _2, _3), std::cref(scene), std::ref(f), std::ref(currPixel));
  }
  for (auto& t : threads) {
    t.join();
  }

  //std::cout << "\rRendering frame " << currentFrame << "..." << " (" << percentFinished << "%)" << std::flush;
  ImageUtil::writeImage(f, "render", currentFrame);
  currentFrame++;
  std::cout << std::endl;
}

void Renderer::renderingWorker(const Scene& scene, Frame& f, std::atomic<int>& currPixel) {
  while (true) {
    int pixel = currPixel--;
    if (pixel < 0) {
      break;
    }
    int x = pixel % f.width;
    int y = pixel / f.width;
    f.buffer[x][y] = renderPixel(scene, x, y);
  }
}

Color Renderer::renderPixel(const Scene& scene, int x, int y) {
  ColorSet c;
  for (int i = 0; i < samplesPerPixel; i++) {
    Line ray = camera.getCameraRayPerturbed(x, y);
    c.add(traceRay(ray, 1, scene));
  }
  return gammaCorrect(c.average());
}

Color Renderer::traceRay(const Line& ray, int depth, const Scene& scene) const {
  if (depth > maxDepth) return Color(0, 0, 0);

  Intersection closest = getClosestIntersection(ray, scene);
  if (closest.hit) {
    auto obj = scene[closest.objectId];
    Vec3 N = obj->normalAt(closest.point);
    Line nextRay = obj->material.sampleNextRay(ray, closest.point, N);
    return obj->getTextureColor(closest.point) * traceRay(nextRay, depth + 1, scene) * reflectance;
  }
  return scene.background(ray);
}

Intersection Renderer::getClosestIntersection(const Line& ray, const Scene& scene) const {
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
