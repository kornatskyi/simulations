#pragma once

#ifndef MATH_UTILS
#define MATH_UTILS
#include "../Config.h"
#include "utils.h"
#include <SFML/Graphics.hpp>
#include <cmath>

float dToR(float degrees) { return degrees * (M_PI / 180); }

Vector2 rotate(float ox, float oy, float x, float y, float angle) {
  return Vector2(
    std::cos(dToR(angle)) * (x - ox) - std::sin(dToR(angle)) * (y - oy) + ox,
    std::sin(dToR(angle)) * (x - ox) + std::cos(dToR(angle)) * (y - oy) + oy);
}

inline sf::Vector2f toSFv2(Vector2 v) { return sf::Vector2(v.x, v.y); }
inline Vector2 toV2(sf::Vector2f v) { return Vector2(v.x, v.y); }

Vector2 rotate(const Vector2 &origin, const Vector2 &point, float angle) {
  return Vector2(std::cos(dToR(angle)) * (point.x - origin.x) -
                   std::sin(dToR(angle)) * (point.y - origin.y) + origin.x,
                 std::sin(dToR(angle)) * (point.x - origin.x) +
                   std::cos(dToR(angle)) * (point.y - origin.y) + origin.y);
}

sf::Vector2f rotatePointAround(const sf::Vector2f &origin,
                               const sf::Vector2f &point, float angle) {
  return sf::Vector2f(std::cos(dToR(angle)) * (point.x - origin.x) -
                        std::sin(dToR(angle)) * (point.y - origin.y) + origin.x,
                      std::sin(dToR(angle)) * (point.x - origin.x) +
                        std::cos(dToR(angle)) * (point.y - origin.y) +
                        origin.y);
}

float getAngleWithOx(const Vector2 &velocity) {
  return std::atan2(velocity.y, velocity.x);
}

sf::Vector2f convertToSFMLCoordinate(Vector2 point) {
  return sf::Vector2f(point.x, -point.y + Config::HEIGHT);
}
#endif
