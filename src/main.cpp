#include "Scene.h"
#include "Sphere.h"
#include "Vec3.h"
#include <iostream>

int main() {
    int x = 400, y = 225;
    Scene scene(x, y);

    auto blue = make_shared<Sphere>(Sphere(Point(0, 0, 2), 0.5, Color(0, 80, 110)/255));
    auto red = make_shared<Sphere>(Sphere(Point(1, 0, 3), 0.5, Color(255, 80, 110)/255));
    auto green = make_shared<Sphere>(Sphere(Point(-0.5, 0.5, 1.3), 0.5, Color(87, 255, 13)/255));

    scene.add("s1", blue);
    scene.add("s2", red);
    scene.add("s3", green);

    scene.render();
    
    std::cout << std::endl;
    return 0;
}