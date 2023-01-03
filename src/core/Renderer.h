#pragma once
#include "Camera.h"
#include "Color.h"
#include "Intersection.h"
#include "Scene.h"

#include <cmath>

class Renderer {
 public:
  Camera camera;
  /**
   * The renderer will shoot many randomly perturbed rays for each pixel and
   * then average out the result. This value determines how many samples for
   * each pixel. A higher value will give a sharper and less noisy image, at the
   * cost of an increased render time.
   */
  int samplesPerPixel;
  /**
   * Max recursion depth of the ray tracer. A higher value will give more
   * accurate reflections and potentially more accurate shadows, at the cost of
   * increase render time.
   */
  int maxDepth;
  /**
   * Used for gamma color correction.
   */
  float gamma{2.0};
  /**
   * Threshold value for detecting if an intersection occured.
   * Ensures that ray originating from object does not intersect with itself.
   */
  float tMin{0.0001};
  const Interval hitInterval{Interval(tMin)};
  /**
   * Fraction of light that remains after each reflection.
   */
  float reflectance{0.5f};

  Renderer(int width, int height, int samplesPerPixel = 100, int maxDepth = 20);
  Renderer(int width, int height, float fov, float focalLength,
           int samplesPerPixel = 100, int maxDepth = 20);
  Renderer(const Camera& camera, int samplesPerPixel = 100, int maxDepth = 20);

  // Renders the scene and saves the rendered image to disk.
  void render(const Scene& scene);
  // Linearly interpolates "property" between its current value and endVal based
  // off numFrames. "property" is passed by reference and modified in this
  // function. It can be any kind of scene or renderer parameter. Renders
  // numFrames + 1 frames in total.
  void renderKeyFrameAnimation(const Scene& scene, float& property,
                               float endVal, int numFrames);

 private:
  int currentFrame = 1;
  // Core function of the ray tracer. Recursively traces the ray up to a maximum
  // recursion depth, and returns the color of the rendered ray.
  Color traceRay(const Line& ray, int depth, const Scene& scene) const;
  // Returns the closest object that intersects with the ray.
  // The "hit" field of the returned object is false iff
  // no intersection occured.
  Intersection getClosestIntersection(const Line& ray,
                                      const Scene& scene) const;
  // Color correct to make it more realistic. colorOut = colorIn ^ (1/gamma).
  Color gammaCorrect(const Color& in) const;
};
