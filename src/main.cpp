#include "Frame.h"
#include "Vec3.h"
#include "ImageUtil.h"
#include "Line.h"
#include "Camera.h"
#include "Sphere.h"
#include <cmath>

#include <iostream>

Color getBackgroundColor(Line ray) {
    Vec3 dir = ray.direction;
    dir.normalize();
    float t = (dir.y + 1.0f) / 2.0f;
    Color bottom = Color(1, 1, 1);
    Color top = Color(0.5, 0.7, 1);
    return bottom+((top-bottom)*t);
}

int main() {
    int x = 400, y = 225;
    Frame f(x, y);
    Camera cam(x, y);
    Sphere s(Point(0, 0, 2), 0.5, Color(0, 80, 110)/255);
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            Line ray = cam.generateCameraRay(j, i);

            Intersection poi = s.rayIntersection(ray);
            //std::cout << "Intersection : " << poi.toString() << std::endl;
            if (poi.hit) {
                f.buffer[j][i] = s.color;              
            }
            else {
                f.buffer[j][i] = getBackgroundColor(ray);
            }
        }
    }
    ImageUtil::writeImage("render.ppm", f);
    return 0;
}