#pragma once
#include "Vec3.h"

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
