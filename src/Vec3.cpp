#include "Vec3.h"
#include <cmath>

Vec3::Vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

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

Vec3 Vec3::operator+(const Vec3& v) const {
    return Vec3(x+v.x, y+v.y, z+v.z);
}
Vec3 Vec3::operator-(const Vec3& v) const {
    return Vec3(x-v.x, y-v.y, z-v.z);
}
Vec3 Vec3::operator*(const float s) const {
    return Vec3(x*s, y*s, z*s);
}
Vec3 Vec3::operator/(const float s) const {
    return Vec3(x/s, y/s, z/s);
}

Vec3 Vec3::operator-() const {
    return Vec3(-x, -y, -z);
}

float Vec3::dot(const Vec3& u, const Vec3& v) {
    return u.x*v.x + u.y*v.y + u.z*v.z;
}

Vec3 Vec3::cross(const Vec3& u, const Vec3& v) {
    return Vec3(u.y*v.z - u.z*v.y, u.z*v.x - u.x*v.z, u.x*v.y - u.y*v.x);
}

float angle(const Vec3& u, const Vec3& v) {
    float cos_theta = Vec3::dot(u, v) / (u.length() * v.length());
    return std::acos(cos_theta);
}

float distance(const Vec3& u, const Vec3& v) {
    return (v - u).length();
}

float distance2(const Vec3& u, const Vec3& v) {
    return (v - u).length2();
}

float Vec3::length() const {
    return std::sqrt(length2());
}

float Vec3::length2() const {
    return dot(*this, *this);
}

Vec3 Vec3::normalize() {
    return (*this) /= length();
}
