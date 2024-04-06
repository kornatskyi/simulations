#include "math_utils.h"
#include "utils.h"
#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef ENTITY_HEADER
#define ENTITY_HEADER

class Entity {
  public:
  Vector2 position;
  float speed;
  float angle;
  Entity() {
    position = Vector2(0.f, 0.f);
    speed = 0.f;
    angle = 0.f;
  }
  Entity(Vector2 position, float speed, float angle)
    : position(position), speed(speed), angle(angle) {}

  void moveForward(float elapsedTime) {
    if (isCollidingWithWall(position)) {
      if (position.x < 0) {
        angle = 180 - angle;
      } else if (position.x > Config::WIDTH) {
        angle = 180 - angle;
      } else if (position.y < 0) {
        angle = 360 - angle;
      } else if (position.y > Config::HEIGHT) {
        angle = 360 - angle;
      }
    }
    position.x = position.x + std::cos(dToR(angle)) * speed * elapsedTime;
    position.y = position.y + std::sin(dToR(angle)) * speed * elapsedTime;
  }

  private:
};

#endif
