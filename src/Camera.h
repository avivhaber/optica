#pragma once
#include "Vec3.h"
#include "Line.h"
#include "MathUtil.h"

class Camera {
    public:
        Point position;

        Camera(
            int imageWidth,
            int imageHeight,
            float horizontalFov = Constants::PI_OVER_2,
            float focalLength = 1);


        Line generateCameraRay(int xIndex, int yIndex);

        float getFocalLength();
        void setFocalLength(float foc);
        float getHorizontalFov();
        void setHorizontalFov(float fov);
        int getImageWidth();
        int getImageHeight();
        void setImageSize(int width, int height);
    
    private:
        int imageWidth; // Image resolution width
        int imageHeight; // Image resolution height
        float focalLength; // Distance from camera to image plane.
        float horizontalFov;
        float imagePlaneWidth;
        float imagePlaneHeight;
        float pixelSize; // Side length of a pixel on the image plane
        Point bottomLeftPixel; // World space location of center bottom left pixel.

        void updateCameraVariables();
};
