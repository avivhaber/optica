#pragma once

#include "Vec3.h"

class Frame {
    public:
        int width;
        int height;
        Color** buffer;

        Frame(int width = 1, int height = 1) : width(width), height(height) {
            buffer = new Color*[width];
            for (int i = 0; i < width; i++) {
                buffer[i] = new Color[height];
            }
        }

        ~Frame() {
            for (int i = 0; i < width; i++) {
                delete[] buffer[i];
            }
            delete[] buffer;
        }
};