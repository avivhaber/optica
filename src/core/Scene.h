#pragma once
#include "Camera.h"
#include "Object.h"
#include "Vec3.h"
#include "Renderer.h"

#include <iostream>
#include <unordered_map>
#include <memory>

using std::make_shared;

class Scene {
    public:
        Camera camera;
        Renderer renderer;

        Scene(int imageWidth, int imageHeight);
        Scene(int imageWidth, int imageHeight, float fov, float foc);
        Scene(Camera cam);

        void add(std::shared_ptr<Object> obj, const std::string& identifier);
        void remove(const std::string& identifier);
        std::shared_ptr<Object> operator[](const std::string& identifier);
        void render();
        void renderAnimation(float& property, float endVal, int frameDuration);
    private:
        std::unordered_map<std::string, std::shared_ptr<Object>> objects;
        int currentFrame = 1;

        Intersection getClosest(const Line& ray);
        Color getRayColor(const Line& ray, int depth);
        static Color getBackgroundColor(const Line& ray);
};