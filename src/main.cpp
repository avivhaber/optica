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
    renderer.samplesPerPixel = 50;

    Color teal = Color(0, 0.31, 0.43);
    Color lightBlue = Color(0.5, 0.8, 0.9);
    auto blue = std::make_shared<Sphere>(Point(0, 0, 2), 0.5, Textures::CHECKERBOARD(teal, lightBlue, 0.05));
    auto red = std::make_shared<Sphere>(Point(1, 0, 3), 0.5, Material(Color(1, 0.31, 0.43), Materials::FUZZY_MIRROR(0)));
    auto green = std::make_shared<Sphere>(Point(-0.5, 0.5, 1.3), 0.5, Color(0.34, 1, 0.06));

    auto floor = std::make_shared<Plane>(Vec3(0, 1, 0), -0.5, Intervals::inf, Intervals::inf, Interval(-1,10), Textures::CHECKERBOARD(Colors::YELLOW, Colors::RED, 0.6));

    scene.add(blue, "sphere1");
    scene.add(red, "sphere2");
    scene.add(green, "sphere3");
    scene.add(floor, "floor");

    renderer.render(scene);

    return 0;
}