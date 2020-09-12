#pragma once
#include "Camera.h"
#include "Object.h"
#include "Vec3.h"
#include <iostream>
#include <unordered_map>
#include <memory>

using std::make_shared;

struct GeneralException : std::exception {
    char const* msg;
    GeneralException(char const* msg) : msg(msg) {}
    ~GeneralException() {
        delete[] msg;
    }
    char const* what() const throw() {
        return msg;
    }
};

class Scene {
    public:
        Camera camera;

        Scene(int imageWidth, int imageHeight);
        Scene(int imageWidth, int imageHeight, float fov, float foc);
        Scene(Camera cam);

        void add(const std::string& identifier, std::shared_ptr<Object> obj);
        void remove(const std::string& identifier);
        std::shared_ptr<Object> operator[](const std::string& identifier);
        void render();
    private:
        std::unordered_map<std::string, std::shared_ptr<Object>> objects;

        Color getRayColor(const Line& ray);
        static Color getBackgroundColor(const Line& ray);
};