#pragma once

#include <Config.h>
#include <SFML/Graphics.hpp>

struct Vector2 {
  float x;
  float y;
  Vector2() = default;
  Vector2(float x, float y) : x(x), y(y) {}

  // Conversion operator to sf::Vector2f
  operator sf::Vector2f() const { return sf::Vector2f(x, y); }

  Vector2 operator+(const Vector2 &v) const {
    return Vector2(v.x + x, v.y + y);
  }

  Vector2 operator-(const Vector2 &v) const {
    return Vector2(x - v.x, y - v.y);
  }

  Vector2 operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
  }

  Vector2 &operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  Vector2 operator/(float scalar) const {
    // You may wish to handle division-by-zero scenarios
    return Vector2(x / scalar, y / scalar);
  }

  Vector2 &operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
  }

  float length() const { return std::sqrt(x * x + y * y); }

  Vector2 normalized() const {
    float len = length();
    if (len != 0.f) {
      return Vector2(x / len, y / len);
    }
    return Vector2(0.f, 0.f); // Or leave it unchanged if zero-length
  }

  Vector2 &normalize() {
    float len = length();
    if (len != 0.f) {
      x /= len;
      y /= len;
    }
    return *this;
  }

  bool nearlyEquals(const Vector2 &v, float epsilon = 1e-5f) const {
    return (std::fabs(x - v.x) < epsilon) && (std::fabs(y - v.y) < epsilon);
  }

  float dot(const Vector2 &v) const { return x * v.x + y * v.y; }

  // Optional: Constructor to initialize from sf::Vector2f
  Vector2(const sf::Vector2f &sfmlVec) : x(sfmlVec.x), y(sfmlVec.y) {}
};