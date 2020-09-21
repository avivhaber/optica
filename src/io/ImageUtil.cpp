#include "Frame.h"
#include "Vec3.h"
#include "ImageUtil.h"
#include "MathUtil.h"

#include <fstream>

const std::string ImageUtil::outputFolder = "out/";
const std::string ImageUtil::ppmExtension = ".ppm";
const int ImageUtil::numDigits = 4;

void ImageUtil::writeImage(const Frame& frame, std::string fileNameBase, int frameNum) {
    std::ofstream ofs(outputFolder + fileNameBase + formatInt(frameNum) + ppmExtension, std::ios_base::out | std::ios_base::binary);
    ofs << "P6" << std::endl << frame.width << ' ' << frame.height << std::endl << "255" << std::endl;

    for (int y = 0; y < frame.height; y++) {
        for (int x = 0; x < frame.width; x++) {
            Color col = frame.buffer[x][frame.height-y-1]; // Image is rendered bottom to top, write in reverse order
            int r = to8Bit(col.x), g = to8Bit(col.y), b = to8Bit(col.z);
            ofs << (char) r << (char) g << (char) b;
        }
    }
    ofs.close();
}

int ImageUtil::to8Bit(float f) {
    return static_cast<int>(255.999 * MathUtil::clip(f, 0.0f, 1.0f));
}

std::string ImageUtil::formatInt(int n) {
    std::string out;
    std::string s = std::to_string(n);
    int leading = numDigits - s.length();
    for (int i = 0; i < leading; i++) {
        out += "0";
    }
    out += s;
    return out;
}
