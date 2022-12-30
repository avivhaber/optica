#include "Scene.h"
#include "Sphere.h"
#include "Plane.h"
#include "Vec3.h"
#include "Colors.h"
#include "MathUtil.h"
#include <iostream>

int main() {
    int x = 800, y = 600;
    Scene scene(x, y);
    scene.renderer.spp = 2000;
    scene.renderer.sampler = &Samplers::rejection;

    auto blue = make_shared<Sphere>(Sphere(Point(0, 0, 2), 0.5, Color(0, 0.31, 0.43)));
    auto red = make_shared<Sphere>(Sphere(Point(1, 0, 3), 0.5, Color(1, 0.31, 0.43)));
    auto green = make_shared<Sphere>(Sphere(Point(-0.5, 0.5, 1.3), 0.5, Color(0.34, 1, 0.06)));

    //auto floor = make_shared<Sphere>(Sphere(Vec3(0, -100.5, 0), 100));
    auto floor = make_shared<Plane>(Plane(Vec3(0, 1, 0), -0.5, Intervals::inf, Intervals::inf, Interval(-1,10)));


    scene.add(blue, "sphere1");
    scene.add(red, "sphere2");
    scene.add(green, "sphere3");
    scene.add(floor, "floor");

    scene.render();

    return 0;
}