#pragma once
#include <iostream>
#include "Frame.h"

namespace ImageUtil {
extern const std::string outputFolder;
extern const std::string ppmExtension;
extern const int numDigits;

void writeImage(const Frame& frame, const std::string& fileNameBase,
                int frameNum);
// Converts [0,1] float to 8-bit integer RGB.
int to8Bit(float f);
// Adds leading 0s to the output filename as necesary.
std::string formatInt(int n);
}  // namespace ImageUtil
