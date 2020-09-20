#include "Scene.h"
#include "Sphere.h"
#include "Vec3.h"
#include "MathUtil.h"
#include <iostream>

int main() {
    int x = 640, y = 360;
    Scene scene(x, y);

    auto blue = make_shared<Sphere>(Sphere(Point(0, 0, 2), 0.5, Color(0, 80, 110)/255));
    auto red = make_shared<Sphere>(Sphere(Point(1, 0, 3), 0.5, Color(255, 80, 110)/255));
    auto green = make_shared<Sphere>(Sphere(Point(-0.5, 0.5, 1.3), 0.5, Color(87, 255, 13)/255));

    auto floor = make_shared<Sphere>(Sphere(Point(0, -100.5, 1), 100, Color(255, 255, 255)/255));


    scene.add("s1", blue);
    scene.add("s2", red);
    scene.add("s3", green);
    scene.add("floor", floor);

    scene.renderAnimation(red->center.y, 2.0, 60);
    
    std::cout << std::endl;
    return 0;
}