#include "Scene.h"
#include "Object.h"
#include "Frame.h"
#include "ImageUtil.h"
#include "Vec3.h"
#include <iostream>
#include <limits>

Scene::Scene(int imageWidth, int imageHeight) : camera(Camera(imageWidth, imageHeight)) {}
Scene::Scene(int imageWidth, int imageHeight, float fov, float foc) : camera(Camera(imageWidth, imageHeight, fov, foc)) {}
Scene::Scene(Camera cam) : camera(cam) {}

// Renders the scene and saves the image to disk.
void Scene::render() {
    std::cout << "\r Rendering frame " << currentFrame << "..." << std::flush;
    Frame f(camera.getImageWidth(), camera.getImageHeight());

    for (int y = 0; y < f.height; y++) {
        for (int x = 0; x < f.width; x++) {
            Line ray = camera.generateCameraRay(x, y);
            f.buffer[x][y] = getRayColor(ray);
        }
    }
    ImageUtil::writeImage(f, "render", currentFrame);
    currentFrame++;
}

Color Scene::getRayColor(const Line& ray) {
    Intersection closestPoi;
    Object* hitObj = nullptr;   
    for (auto& e : objects) {
        Intersection tempPoi = e.second->rayIntersection(ray);    
        if (tempPoi.hit && tempPoi.dist2 < closestPoi.dist2) {
            closestPoi = tempPoi;
            hitObj = e.second.get();
        }
    }
    if (hitObj != nullptr) {
        return hitObj->color;
    }
    return getBackgroundColor(ray);
}

Color Scene::getBackgroundColor(const Line& ray) {
    Vec3 dir = ray.direction;
    dir.normalize();
    float t = (dir.y + 1.0f) / 2.0f;
    Color bottom = Color(1, 1, 1);
    Color top = Color(0.5, 0.7, 1);
    return bottom+((top-bottom)*t);
}

// Adds an object to scene. Unlike the [] operator, add
// checks to see if the identifier exists to avoid overwriting.
void Scene::add(const std::string& identifier, std::shared_ptr<Object> obj) {
    if (objects.find(identifier) != objects.end()) {
        throw GeneralException("Identifier already exists in scene.");
    }
    objects[identifier] = obj;
}

// Removes an object from the scene.
void Scene::remove(const std::string& identifier) {
    int n = objects.erase(identifier);
    if (n == 0) {
        throw GeneralException("Identifier not found.");
    }
}

std::shared_ptr<Object> Scene::operator[](const std::string& identifier) {
    return objects[identifier];
}