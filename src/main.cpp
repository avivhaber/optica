#include "Scene.h"
#include "Sphere.h"
#include "Vec3.h"
#include <iostream>

int main() {
    int x = 400, y = 225;
    Scene scene(x, y);

    auto sphere1 = make_shared<Sphere>(Sphere(Point(0, 0, 2), 0.5, Color(0, 80, 110)/255));
    auto sphere2 = make_shared<Sphere>(Sphere(Point(1, 0, 3), 0.5, Color(255, 80, 110)/255));
    auto sphere3 = make_shared<Sphere>(Sphere(Point(-0.5, 0.5, 1.3), 0.5, Color(87, 255, 13)/255));

    scene.add("s1", sphere1);
    scene.add("s2", sphere2);
    scene.add("s3", sphere3);

    scene.render();
    return 0;
}