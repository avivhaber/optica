#pragma once
#include "Frame.h"
#include <iostream>

namespace ImageUtil {
    extern const std::string outputFolder;
    
    void writeImage(std::string fileName, const Frame& frame);
    int to8Bit(float f);
}
