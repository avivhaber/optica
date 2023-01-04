#include <memory>
#include "Color.h"
#include "Plane.h"
#include "Renderer.h"
#include "Scene.h"
#include "Sphere.h"
#include "Texture.h"
#include "Vec3.h"

int main() {
  int x = 1920;
  int y = 1080;
  Scene scene;
  Renderer renderer(x, y);
  renderer.samplesPerPixel = 2000;

  Material blueCheckerboard(Textures::CHECKERBOARD(Colors::DARK_BLUE, Colors::LIGHT_CYAN, 0.05));
  Material redCheckerboard(Textures::CHECKERBOARD(Colors::WHITE, Colors::RED, 0.6));
  Material pinkMirror(Colors::SALMON, Materials::FUZZY_MIRROR(0.1));
  float sphereRadius = 0.5f;

  auto green = std::make_shared<Sphere>(Point(-1, 0.2, 1.9), sphereRadius, Colors::BRIGHT_GREEN);
  auto blue = std::make_shared<Sphere>(Point(0, 0, 2), sphereRadius, blueCheckerboard);
  auto pink = std::make_shared<Sphere>(Point(1, 0, 3), sphereRadius, pinkMirror);
  auto floor = std::make_shared<Plane>(Vec3(0, 1, 0), -0.5, Intervals::inf, Intervals::inf,
                                       Interval(-1, 10), redCheckerboard);

  scene.add(green, "sphere1");
  scene.add(blue, "sphere2");
  scene.add(pink, "sphere3");
  scene.add(floor, "floor");

  renderer.render(scene);

  return 0;
}