#pragma once

#include "../Config.h"
#include "utils.h"
#include <SFML/Graphics.hpp>
#include <cmath>
namespace MathUtils {

inline float dToR(float degrees) { return degrees * (M_PI / 180.0f); }

inline Vector2 rotate(const Vector2 &origin, const Vector2 &point,
                      float angle) {
  float rad = dToR(angle);
  float cosA = std::cos(rad);
  float sinA = std::sin(rad);
  return Vector2(
      cosA * (point.x - origin.x) - sinA * (point.y - origin.y) + origin.x,
      sinA * (point.x - origin.x) + cosA * (point.y - origin.y) + origin.y);
}

inline sf::Vector2f rotatePointAround(const sf::Vector2f &origin,
                                      const sf::Vector2f &point, float angle) {
  Vector2 rotated =
      rotate(Vector2(origin.x, origin.y), Vector2(point.x, point.y), angle);
  return sf::Vector2f(rotated.x, rotated.y);
}

} // namespace MathUtils