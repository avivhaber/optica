#pragma once
#include "Frame.h"
#include <iostream>

namespace ImageUtil {
    extern const std::string outputFolder;
    extern const std::string ppmExtension;
    extern const int numDigits;
    
    void writeImage(const Frame& frame, std::string fileNameBase, int frameNum);
    int to8Bit(float f);
    std::string formatInt(int n);
}
