#include "Scene.h"
#include "Sphere.h"
#include "Plane.h"
#include "Vec3.h"
#include "Colors.h"
#include "MathUtil.h"
#include <iostream>
#include <memory>

int main() {
    int x = 1280, y = 720;
    Scene scene(x, y);
    scene.renderer.samplesPerPixel = 1;
    scene.renderer.sampler = &Samplers::rejection;

    auto blue = std::make_shared<Sphere>(Point(0, 0, 2), 0.5, Color(0, 0.31, 0.43));
    auto red = std::make_shared<Sphere>(Point(1, 0, 3), 0.5, Color(1, 0.31, 0.43));
    auto green = std::make_shared<Sphere>(Point(-0.5, 0.5, 1.3), 0.5, Color(0.34, 1, 0.06));
    auto floor = std::make_shared<Plane>(Vec3(0, 1, 0), -0.5, Intervals::inf, Intervals::inf, Interval(-1,10));

    scene.add(blue, "sphere1");
    scene.add(red, "sphere2");
    scene.add(green, "sphere3");
    scene.add(floor, "floor");

    scene.render();

    return 0;
}