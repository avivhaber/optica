#include "Frame.h"
#include "Vec3.h"
#include "ImageUtil.h"

#include <fstream>

const std::string ImageUtil::outputFolder = "out/";

void ImageUtil::writeImage(std::string fileName, const Frame& frame) {
    std::ofstream ofs(outputFolder + fileName, std::ios_base::out | std::ios_base::binary);
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
    return static_cast<int>(255.999 * f);
}
