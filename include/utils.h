#ifndef UTILS
#define UTILS

struct Vector2 {
  float x;
  float y;
  Vector2() = default;
  Vector2(float x, float y) : x(x), y(y) {}
};

inline bool isCollidingWithWall(const Vector2 &point) {
  return point.x < 0 || point.y < 0 || point.x > Config::WIDTH ||
         point.y > Config::HEIGHT;
}

#endif