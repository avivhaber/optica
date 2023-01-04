#pragma once
#include "Background.h"
#include "Object.h"

#include <functional>
#include <memory>
#include <unordered_map>

// Represent a renderable scene. Essentially just a list of objects, along with a background.
class Scene {
 public:
  // Adds an object to scene with an identifier. Unlike the [] operator, add
  // checks to see if the identifier exists to avoid overwriting.
  void add(std::shared_ptr<Object> obj, const std::string& identifier);
  // Removes an object from the scene.
  void remove(const std::string& identifier);
  // Returns a shared_ptr of the scene object corresponding to the identifier.
  std::shared_ptr<Object> operator[](const std::string& identifier) const;
  // Const iterator pointing to first object.
  std::unordered_map<std::string, std::shared_ptr<Object>>::const_iterator begin() const;
  // Const iterator pointing to one spot past the last object.
  std::unordered_map<std::string, std::shared_ptr<Object>>::const_iterator end() const;
  // The background color of the scene.
  BackgroundGenerator background = Backgrounds::BLUE_SKY();

 private:
  std::unordered_map<std::string, std::shared_ptr<Object>> objects;
};
