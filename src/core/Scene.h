#pragma once
#include "Backgrounds.h"
#include "Object.h"

#include <functional>
#include <memory>
#include <unordered_map>

class Scene {
 public:
  // Adds an object to scene with an identifier. Unlike the [] operator, add
  // checks to see if the identifier exists to avoid overwriting.
  void add(std::shared_ptr<Object> obj, const std::string& identifier);
  // Removes an object from the scene.
  void remove(const std::string& identifier);
  // Returns a shared_ptr of the scene object corresponding to the identifier.
  std::shared_ptr<Object> operator[](const std::string& identifier) const;
  std::unordered_map<std::string, std::shared_ptr<Object>>::const_iterator begin() const;
  std::unordered_map<std::string, std::shared_ptr<Object>>::const_iterator end() const;

  BackgroundGenerator background = Backgrounds::blueSky();

 private:
  std::unordered_map<std::string, std::shared_ptr<Object>> objects;
};
