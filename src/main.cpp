#include "Frame.h"
#include "Color.h"
#include "ImageUtil.h"
#include "Sphere.h"


#include <iostream>

int main() {
    Frame f(2, 2);
    Sphere s(Point(1,1,1), 23);
    Color**& b = f.buffer;
    b[0][0] = Color(255, 255, 255);
    b[1][0] = Color(255, 0, 0);
    b[0][1] = Color(255, 0, 255);
    b[1][1] = Color(255, 255, 0);

    writeImage("render.ppm", f);
    std::cout << s.radius << "\n";
    return 0;
}