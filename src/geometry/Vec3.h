#pragma once
#include <string>

/*
A class for representing geometric vectors in 3 dimensions.
A Vec3 is considered invalid if any of its components are NaN.
This can be checked with isValdid().
*/
class Vec3 {
    public:
        float x;
        float y;
        float z;

        Vec3(float x = 0, float y = 0, float z = 0);
        
        Vec3& operator+=(const Vec3& v);
        Vec3& operator-=(const Vec3& v);
        Vec3& operator*=(const float s);
        Vec3& operator/=(const float s);
        Vec3 operator+(const Vec3& v) const;
        Vec3 operator-(const Vec3& v) const;
        Vec3 operator*(const Vec3& v) const;
        Vec3 operator*(const float s) const;
        Vec3 operator/(const float s) const;
        Vec3 operator-() const;

        static float dot(const Vec3& u, const Vec3& v);
        static Vec3 cross(const Vec3& u, const Vec3& v);
        static float angle(const Vec3& u, const Vec3& v);
        static float distance(const Vec3& u, const Vec3& v);
        static float distance2(const Vec3& u, const Vec3& v);
        float length() const;
        float length2() const;
        Vec3 normalize() const;
        bool isValid();
        static Vec3 randVec(float min, float max);
        static Vec3 randomUnitVec();
        std::string toString() const;
};


using Point = Vec3; // A point in 3D
using Color = Vec3; // An RGB color. Ensure that each channel is between 0 and 1.
