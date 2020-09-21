#pragma once

class RenderOptions {
    public:
        int spp; // Samples per pixel.
        RenderOptions(int spp = 10) : spp(spp) {}
};