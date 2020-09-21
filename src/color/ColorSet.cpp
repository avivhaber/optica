#include "ColorSet.h"
#include "Vec3.h"

ColorSet::ColorSet() : x(0), y(0), z(0), samples(0) {}

void ColorSet::add(Color c) {
    x += static_cast<double>(c.x);
    y += static_cast<double>(c.y);
    z += static_cast<double>(c.z);
    samples++;
}

Color ColorSet::average() {
    return Color(static_cast<float>(x/samples), static_cast<float>(y/samples), static_cast<float>(z/samples));
}

void ColorSet::clear() {
    x = 0;
    y = 0;
    z = 0;
    samples = 0;
}
