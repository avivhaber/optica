#include "Frame.h"
#include "Vec3.h"
#include "ImageUtil.h"
#include "Line.h"
#include "Camera.h"

#include <iostream>

Color getColor(Line ray) {
    float t = (ray.direction.y + 1.0f) / 2.0f;
    Color bottom = Color(1, 1, 1);
    Color top = Color(0.5, 0.7, 1);
    return bottom+((top-bottom)*t);
}

int main() {
    int x = 400, y = 225;
    Frame f(x, y);
    Camera cam(x, y);
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            Line ray = cam.generateCameraRay(j, i);
            //std::cout << ray.direction.toString() << std::endl;
            f.buffer[j][i] = getColor(ray);
        }
    }

    ImageUtil::writeImage("render.ppm", f);
    return 0;
}