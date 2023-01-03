#include "Scene.h"
#include "Renderer.h"
#include "Sphere.h"
#include "Plane.h"
#include "Vec3.h"
#include "Color.h"
#include "MathUtil.h"
#include "Texture.h"
#include <iostream>
#include <memory>

int main() {
    int x = 1280;
    int y = 720;
    Scene scene;
    Renderer renderer(x, y);
    renderer.samplesPerPixel = 1000;

    auto blue = std::make_shared<Sphere>(Point(0, 0, 2), 0.5, Material(Textures::CHECKERBOARD(Colors::DARK_BLUE, Colors::LIGHT_CYAN, 0.05)));
    auto red = std::make_shared<Sphere>(Point(1, 0, 3), 0.5, Material(Colors::SALMON, Materials::FUZZY_MIRROR(0)));
    auto green = std::make_shared<Sphere>(Point(-0.5, 0.5, 1.3), 0.5, Colors::BRIGHT_GREEN);
    auto floor = std::make_shared<Plane>(Vec3(0, 1, 0), -0.5, Intervals::inf, Intervals::inf, Interval(-1,10), Material(Textures::CHECKERBOARD(Colors::WHITE, Colors::RED, 0.6)));

    scene.add(blue, "sphere1");
    scene.add(red, "sphere2");
    scene.add(green, "sphere3");
    scene.add(floor, "floor");

    renderer.render(scene);

    return 0;
}