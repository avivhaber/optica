#pragma once
#include <string>

/*
A class for representing geometric vectors in 3 dimensions.
A Vec3 is considered invalid iff any of its components are NaN.
This can be checked with isValid().
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
  // element-wise multiplication.
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
  bool nearZero();
  // Each component is uniformly distributed over [min, max)
  static Vec3 randVec(float min, float max);
  // Returns a uniformly distributed unit vector.
  // Uses method described here: https://math.stackexchange.com/a/1586015
  static Vec3 randomUnitVec();
  std::string toString() const;

  friend bool operator==(const Vec3& v1, const Vec3& v2);
  friend bool operator!=(const Vec3& v1, const Vec3& v2);
};

bool operator==(const Vec3& v1, const Vec3& v2);
bool operator!=(const Vec3& v1, const Vec3& v2);

// A point in 3D. This is an alias for Vec3.
// In practice, you usually use a Vec3 to refer to a direction,
// and a Point to refer to some location in 3D space.
// Picking the proper type can make code more readable.
using Point = Vec3;
