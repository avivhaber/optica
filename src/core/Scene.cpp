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
    Frame f(camera.getImageWidth(), camera.getImageHeight());

    for (int y = 0; y < f.height; y++) {
        for (int x = 0; x < f.width; x++) {
            ColorSet c;
            for (int i = 0; i < renderer.spp; i++) {
                Line ray = camera.getCameraRayPertrubed(x, y);
                c.add(getRayColor(ray, 1));
            }
            f.buffer[x][y] = renderer.gammaCorrect(c.average());
        }
        // Update render progress
        std::cout << "\rRendering frame " << currentFrame << "..." << " (" << (100*y*f.width)/(f.width*f.height) << "%)" << std::flush;
    }
    ImageUtil::writeImage(f, "render", currentFrame);
    currentFrame++;
}

// Core function of ray tracer. Recursively gets the color of a given ray.
Color Scene::getRayColor(const Line& ray, int depth) {
    if (depth >= renderer.maxDepth) return Color(0, 0, 0);

    Intersection closest = getClosest(ray);
    if (closest.hit) {
        Vec3 N = closest.obj->normalAt(closest.point);
        Line nextRay = renderer.sampler->sampleNextRay(closest.point, N);
        //float cosTheta = Vec3::dot(nextRay.direction.normalize(), N);
        //return closest.obj->colorAt(closest.point) * cosTheta;
        return closest.obj->colorAt(closest.point) * getRayColor(nextRay, depth+1) * Constants::ONE_OVER_PI;
    }
    return getBackgroundColor(ray);
}

// Returns the closest object that intersects with ray.
// The "hit" field of the returned object is false iff
// there are no intersections.
Intersection Scene::getClosest(const Line& ray) {
    Intersection closest(false);
    for (auto& e : objects) {
        Intersection curr = e.second->rayIntersection(ray, Interval(renderer.tMin));
        if (curr.hit && curr.t < closest.t) {
            closest = curr;
        }
    }
    return closest;
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
