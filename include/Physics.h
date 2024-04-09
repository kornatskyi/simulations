#ifndef PHYSICS_HEADER
#define PHYSICS_HEADER
#include "Entity.h"
#include "math_utils.h"
#include "utils.h"
#include <map>
#include <set>
#include <tuple>

#include <math.h>

class Physics {
  public:
  std::map<std::tuple<int, int>, std::set<Entity>> entitiesByCell;
  float cellSize;

  Physics() {
    cellSize = 100;

    for (u_int i = 0; i <= u_int(Config::WIDTH / cellSize); i++) {
      for (u_int j = 0; j <= u_int(Config::HEIGHT / cellSize); j++) {
        entitiesByCell[std::tuple(i * cellSize, j * cellSize)] =
          std::set<Entity>();
      }
    }
  }

  inline bool areColliding(const Entity &e1, const Entity &e2) {
    return e1.radius + e2.radius >=
           sqrt(pow((e2.position.x - e1.position.x), 2) +
                pow((e2.position.y - e1.position.y), 2));
  }

  std::vector<std::tuple<Entity, Entity>>
  collidingEntities(const std::vector<Entity> &entities) {
    update(entities);
    std::vector<std::tuple<Entity, Entity>> collidingEntities;
    for (auto const &imap : entitiesByCell) {

      for (auto const &e1 : imap.second) {
        for (auto const &e2 : imap.second) {
          if (&e1 != &e2 && areColliding(e1, e2)) {
            collidingEntities.push_back(std::tuple(e1, e2));
          }
        }
      }
    }
    return collidingEntities;
  }

  private:
  void update(const std::vector<Entity> &entities) {

    for (auto const &imap : entitiesByCell) {
      entitiesByCell[imap.first] = std::set<Entity>();
    }

    for (auto &entity : entities) {
      auto t = std::tuple(int(entity.position.x / cellSize) * cellSize,
                          int(entity.position.y / cellSize) * cellSize);
      entitiesByCell.at(t).insert(entity);
    }
  }
};

#endif
