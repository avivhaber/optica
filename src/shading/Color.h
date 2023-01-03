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

namespace Colors {
    inline const Color BLACK {0, 0, 0};
    inline const Color WHITE {1, 1, 1};
    inline const Color RED {1, 0, 0};
    inline const Color GREEN {0, 1, 0};
    inline const Color BLUE {0, 0, 1};
    inline const Color YELLOW {1, 1, 0};
    inline const Color CYAN {0, 1, 1};
    inline const Color MAGENTA {1, 0, 1};
    inline const Color SKY_BLUE {0.5, 0.7, 1};
}
