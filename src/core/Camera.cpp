#include "Camera.h"
#include "Vec3.h"
#include "Line.h"
#include <cmath>
#include <iostream>

Camera::Camera(
    int imageWidth,
    int imageHeight,
    float horizontalFov,
    float focalLength) : 
        position(Point(0, 0, 0)),
        imageWidth(imageWidth),
        imageHeight(imageHeight),
        focalLength(focalLength),
        horizontalFov(horizontalFov) {
    updateCameraVariables();
}

/**
 * Generates a ray originating from the camera and going through the image plane.
 * Ensure that 0<=xIndex<=imageWidth-1 and similarly for yIndex.
 * As an example, (0, 0) represents the bottom left, and (imageWidth-1, imageHeight-1) represents the top right.
*/ 
Line Camera::getCameraRay(float xIndex, float yIndex) {
    Point pixel = bottomLeftPixel;
    pixel += Vec3(pixelSize * xIndex, pixelSize * yIndex, 0);
    return Line(position, pixel-position);
}

// Same as getCameraRay, but randomly pertrubes the position within a viewport pixel.
// Used for AA and smoothing.
Line Camera::getCameraRayPertrubed(int xIndex, int yIndex) {
    float xoff = MathUtil::rand() - 0.5f;
    float yoff = MathUtil::rand() - 0.5f;
    return getCameraRay(xIndex + xoff, yIndex + yoff);
}

void Camera::updateCameraVariables() {
    float invAspectRatio = (float)(imageHeight-1) / (float)(imageWidth-1);
    viewportWidth = 2 * focalLength * tan(horizontalFov / 2.0f);
    viewportHeight = viewportWidth * invAspectRatio;
    pixelSize = viewportWidth / (imageWidth - 1);
    bottomLeftPixel = position;
    bottomLeftPixel.z += focalLength;
    bottomLeftPixel.y -= viewportHeight / 2.0f;
    bottomLeftPixel.x -= viewportWidth / 2.0f;
}

float Camera::getFocalLength() {return focalLength;}
float Camera::getHorizontalFov() {return horizontalFov;}
int Camera::getImageWidth() {return imageWidth;}
int Camera::getImageHeight() {return imageHeight;}

void Camera::setFocalLength(float foc) {
    focalLength = foc;
    updateCameraVariables();
}
void Camera::setHorizontalFov(float fov) {
    horizontalFov = fov;
    updateCameraVariables();
}
void Camera::setImageSize(int width, int height) {
    imageWidth = width;
    imageHeight = height;
    updateCameraVariables();
}