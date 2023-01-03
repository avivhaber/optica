#pragma once
#include "Vec3.h"
#include "Line.h"
#include "MathUtil.h"

class Camera {
    public:
        Point position {Point(0, 0, 0)};

        Camera(
            int imageWidth,
            int imageHeight,
            float horizontalFov = Constants::PI_OVER_2,
            float focalLength = 1);

        /**
         * Generates a ray originating from the camera and going through the center of the specified pixel in the image plane.
         * Ensure that 0<=xIndex<=imageWidth-1 and 0<=yIndex<=imageHeight-1.
         * (0, 0) represents the bottom left pixel, and (imageWidth-1, imageHeight-1) represents the top right pixel.
        */ 
        Line getCameraRay(float xIndex, float yIndex) const;
        /**
         * Works the same as getcamerRay, but the returned ray will point to a uniformly random position in the specified pixel.
         * This function is useful for supersmapling.
         * Ensure that 0<=xIndex<=imageWidth-1 and 0<=yIndex<=imageHeight-1.
         * (0, 0) represents the bottom left pixel, and (imageWidth-1, imageHeight-1) represents the top right pixel.
        */ 
        Line getCameraRayPertrubed(int xIndex, int yIndex) const;

        float getFocalLength() const; // Gets the focal length (distance from image plane to focal point).
        void setFocalLength(float foc); // Sets the focal length (distance from image plane to focal point).
        float getHorizontalFov() const; // Gets the horizontal field-of-view, in radians.
        void setHorizontalFov(float fov); // Sets the horizontal field-of-view, in radians.
        int getImageWidth() const; // Gets the image width, in pixels.
        int getImageHeight() const; // Gets the image height, in pixels.
        void setImageSize(int width, int height); // Sets the image width and height, in pixels.
    
    private:
        int imageWidth; // Image width in pixels.
        int imageHeight; // Image height in pixels.
        float focalLength; // Distance from the camera's focal point to the image plane.
        float horizontalFov; // Angle in radians of the horizontal field-of-view.
        float viewportWidth; // Width of the image plane.
        float viewportHeight; // Height of the image plane.
        float pixelSize; // Side length of a pixel on the image plane.
        Point bottomLeftPixel; // World space location of the center of the bottom left pixel.

        // If any setter is called, all the variables need to be recomputed.
        void updateCameraVariables();
};
