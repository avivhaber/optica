#include "Vec3.h"
#include <cmath>
#include <string>
#include "MathUtil.h"

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

Vec3& Vec3::operator+=(const Vec3& v) {
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}
Vec3& Vec3::operator-=(const Vec3& v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}
Vec3& Vec3::operator*=(const float s) {
  x *= s;
  y *= s;
  z *= s;
  return *this;
}
Vec3& Vec3::operator/=(const float s) {
  x /= s;
  y /= s;
  z /= s;
  return *this;
}

Vec3 Vec3::operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
Vec3 Vec3::operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
Vec3 Vec3::operator*(const Vec3& v) const { return Vec3(x * v.x, y * v.y, z * v.z); }
Vec3 Vec3::operator*(const float s) const { return Vec3(x * s, y * s, z * s); }
Vec3 Vec3::operator/(const float s) const { return Vec3(x / s, y / s, z / s); }

Vec3 Vec3::operator-() const { return Vec3(-x, -y, -z); }

float Vec3::dot(const Vec3& u, const Vec3& v) { return u.x * v.x + u.y * v.y + u.z * v.z; }

Vec3 Vec3::cross(const Vec3& u, const Vec3& v) {
  return Vec3(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
}

float Vec3::angle(const Vec3& u, const Vec3& v) {
  float cos_theta = Vec3::dot(u, v) / (u.length() * v.length());
  return std::acos(cos_theta);
}

float Vec3::distance(const Vec3& u, const Vec3& v) { return (v - u).length(); }

float Vec3::distance2(const Vec3& u, const Vec3& v) { return (v - u).length2(); }

float Vec3::length() const { return std::sqrt(length2()); }

float Vec3::length2() const { return dot(*this, *this); }

Vec3 Vec3::normalize() const { return (*this) / length(); }

bool Vec3::isValid() { return !std::isnan(x) && !std::isnan(y) && !std::isnan(z); }

bool Vec3::nearZero() {
  float t = 1e-8;
  return std::abs(x) < t && std::abs(y) < t && std::abs(z) < t;
}

Vec3 Vec3::randVec(float min, float max) {
  return Vec3(MathUtil::rand(min, max), MathUtil::rand(min, max), MathUtil::rand(min, max));
}

Vec3 Vec3::randomUnitVec() {
  float theta = MathUtil::rand(0, 2 * Constants::PI);
  float z = MathUtil::rand(-1, 1);
  float r = sqrt(1 - z * z);
  return Vec3(r * std::cos(theta), r * std::sin(theta), z);
}

std::string Vec3::toString() const {
  return "x: " + std::to_string(x) + ", y: " + std::to_string(y) + ", z: " + std::to_string(z);
}

bool operator==(const Vec3& v1, const Vec3& v2) {
  return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

bool operator!=(const Vec3& v1, const Vec3& v2) { return !(v1 == v2); }
