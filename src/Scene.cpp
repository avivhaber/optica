#include "Scene.h"
#include "Object.h"
#include "Frame.h"
#include "Sphere.h"
#include "ImageUtil.h"
#include "MathUtil.h"
#include "ColorSet.h"
#include "Vec3.h"
#include <iostream>
#include <limits>
#include <algorithm>

Point light(2, 2, 0);

Scene::Scene(int imageWidth, int imageHeight) : camera(Camera(imageWidth, imageHeight)) {}
Scene::Scene(int imageWidth, int imageHeight, float fov, float foc) : camera(Camera(imageWidth, imageHeight, fov, foc)) {}
Scene::Scene(Camera cam) : camera(cam) {}

// Renders the scene and saves the image to disk.
void Scene::render() {
    std::cout << "\rRendering frame " << currentFrame << "..." << std::flush;
    Frame f(camera.getImageWidth(), camera.getImageHeight());

    for (int y = 0; y < f.height; y++) {
        for (int x = 0; x < f.width; x++) {
            ColorSet c;
            for (int i = 0; i < renderer.spp; i++) {
                float xoff = MathUtil::rand() - 0.5f;
                float yoff = MathUtil::rand() - 0.5f;
                Line ray = camera.generateCameraRay(x+xoff, y+yoff);
                c.add(getRayColor(ray));
            }
            f.buffer[x][y] = c.average();
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
        if (tempPoi.hit && tempPoi.t < closestPoi.t) {
            closestPoi = tempPoi;
            hitObj = e.second.get();
        }
    }
    if (hitObj != nullptr) {
        Vec3 lightVec = (light-closestPoi.poi).normalize();
        Vec3 N = hitObj->normalAt(closestPoi.poi);
        float factor = Vec3::dot(lightVec, N);
        return hitObj->colorAt(closestPoi.poi) * (factor);
    }
    return getBackgroundColor(ray);
}

Color Scene::getBackgroundColor(const Line& ray) {
    Vec3 dir = ray.direction.normalize();
    float t = (dir.y + 1.0f) / 2.0f;
    Color bottom = Color(1, 1, 1);
    Color top = Color(0.5, 0.7, 1);
    return bottom+((top-bottom)*t);
}

void Scene::renderAnimation(float& property, float endVal, int frameDuration) {
    float delta = (endVal-property) / (float)frameDuration;

    render();
    for (int i = 0; i < frameDuration; i++) {
        property += delta;
        render();
    }
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