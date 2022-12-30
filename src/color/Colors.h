#pragma once

#include "Vec3.h"

// An RGB color. Each channel's value is between 0 and 1.
using Color = Vec3;

// A class for keeping track of and averaging many color samples.
// Uses doubles instead of floats, in the case of very many samples.
class ColorSet {
    public:
        ColorSet();
        void add(Color c);
        Color average();
        void clear();
    private:
        double x, y, z;
        long long samples;
};
