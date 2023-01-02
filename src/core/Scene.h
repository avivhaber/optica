#pragma once
#include "Camera.h"
#include "Object.h"
#include "Vec3.h"
#include "Colors.h"
#include "Renderer.h"

#include <iostream>
#include <unordered_map>
#include <memory>
#include <functional>

// Default implementation of backgroundColor.
// Displays a blue gradient based off ray's y-value.
Color skyGradientBackground(const Line& ray);

class Scene {
    public:
        Camera camera;
        Renderer renderer;

        Scene(int imageWidth, int imageHeight);
        Scene(int imageWidth, int imageHeight, float fov, float foc);
        Scene(Camera cam);

        // Adds an object to scene with an identifier. Unlike the [] operator, add
        // checks to see if the identifier exists to avoid overwriting.
        void add(std::shared_ptr<Object> obj, const std::string& identifier);
        // Removes an object from the scene.
        void remove(const std::string& identifier);
        // Returns a shared_ptr of the scene object corresponding to the identifier.
        std::shared_ptr<Object> operator[](const std::string& identifier);
        std::unordered_map<std::string, std::shared_ptr<Object>>::iterator begin();
        std::unordered_map<std::string, std::shared_ptr<Object>>::iterator end();

        void render();
        void renderAnimation(float& property, float endVal, int frameDuration);
        // The background color of this Scene. Can vary depending on ray direction.
        // More specifically: Given a ray that does not intersect with any object
        // and will shoot off to the sky, return the Color this ray should use.
        std::function<Color(const Line&)> backgroundColor = skyGradientBackground;

    private:
        std::unordered_map<std::string, std::shared_ptr<Object>> objects;
        int currentFrame = 1;

        Intersection getClosest(const Line& ray);
        Color getRayColor(const Line& ray, int depth);
};
