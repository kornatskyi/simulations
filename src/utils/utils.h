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

  // Optional: Constructor to initialize from sf::Vector2f
  Vector2(const sf::Vector2f &sfmlVec) : x(sfmlVec.x), y(sfmlVec.y) {}
};

inline bool isCollidingWithWall(const Vector2 &point) {
  return point.x < 0 || point.y < 0 || point.x > Config::getInstance().width ||
         point.y > Config::getInstance().height;
}
