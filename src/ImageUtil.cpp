#include "Frame.h"
#include "Color.h"
#include "ImageUtil.h"

#include <fstream>

const std::string outputFolder = "out/";

void writeImage(std::string fileName, const Frame& frame) {
    std::ofstream ofs(outputFolder + fileName, std::ios_base::out | std::ios_base::binary);
    ofs << "P6" << std::endl << frame.width << ' ' << frame.height << std::endl << "255" << std::endl;

    for (int y = 0; y < frame.height; y++) {
        for (int x = 0; x < frame.width; x++) {
            ofs << (char) frame.buffer[x][y].r << (char) frame.buffer[x][y].g << (char) frame.buffer[x][y].b;
        }
    }
    ofs.close();
}
