#include "Scene.h"
#include "Sphere.h"
#include "Plane.h"
#include "Vec3.h"
#include "MathUtil.h"
#include <iostream>

int main() {
    int x = 1280, y = 720;
    Scene scene(x, y);
    scene.renderer.spp = 100;

    auto blue = make_shared<Sphere>(Sphere(Point(0, 0, 2), 0.5, Color(0, 80, 110)/255));
    auto red = make_shared<Sphere>(Sphere(Point(1, 0, 3), 0.5, Color(255, 80, 110)/255));
    auto green = make_shared<Sphere>(Sphere(Point(-0.5, 0.5, 1.3), 0.5, Color(87, 255, 13)/255));

    auto floor = make_shared<Plane>(Plane(Vec3(0, 1, 0), -0.5));


    scene.add("s1", blue);
    scene.add("s2", red);
    scene.add("s3", green);
    scene.add("floor", floor);

    scene.render();
    
    std::cout << std::endl;
    return 0;
}