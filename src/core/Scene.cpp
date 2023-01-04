#include "Scene.h"
#include "Exceptions.h"
#include "Object.h"

void Scene::add(std::shared_ptr<Object> obj, const std::string& identifier) {
  if (objects.find(identifier) != objects.end()) {
    throw GeneralException("Identifier already exists in scene.");
  }
  objects[identifier] = obj;
}

void Scene::remove(const std::string& identifier) {
  int n = objects.erase(identifier);
  if (n == 0) {
    throw GeneralException("Identifier not found.");
  }
}

std::shared_ptr<Object> Scene::operator[](const std::string& identifier) const {
  return objects.at(identifier);
}

std::unordered_map<std::string, std::shared_ptr<Object>>::const_iterator Scene::begin() const {
  return objects.cbegin();
}
std::unordered_map<std::string, std::shared_ptr<Object>>::const_iterator Scene::end() const {
  return objects.cend();
}
