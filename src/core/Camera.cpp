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
        imageWidth(imageWidth),
        imageHeight(imageHeight),
        focalLength(focalLength),
        horizontalFov(horizontalFov) {
    updateCameraVariables();
}

Line Camera::getCameraRay(float xIndex, float yIndex) {
    Point pixel = bottomLeftPixel;
    pixel += Vec3(pixelSize * xIndex, pixelSize * yIndex, 0);
    return Line(position, pixel-position);
}

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
