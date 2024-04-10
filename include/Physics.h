#ifndef PHYSICS_HEADER
#define PHYSICS_HEADER
#include "Entity.h"
#include "math_utils.h"
#include "utils.h"
#include <map>
#include <math.h>
#include <memory>
#include <set>
#include <tuple>

class Physics {
  public:
  std::map<std::tuple<int, int>, std::set<std::shared_ptr<Entity>>>
    entitiesByCell;
  float cellSize;

  Physics() {
    cellSize = 100;

    for (u_int i = 0; i <= u_int(Config::WIDTH / cellSize); i++) {
      for (u_int j = 0; j <= u_int(Config::HEIGHT / cellSize); j++) {
        entitiesByCell[std::tuple(i * cellSize, j * cellSize)] =
          std::set<std::shared_ptr<Entity>>();
      }
    }
  }

  inline bool areColliding(const std::shared_ptr<Entity> e1,
                           const std::shared_ptr<Entity> &e2) {
    return e1->radius + e2->radius >=
           sqrt(pow((e2->position.x - e1->position.x), 2) +
                pow((e2->position.y - e1->position.y), 2));
  }

  std::vector<std::tuple<std::shared_ptr<Entity>, std::shared_ptr<Entity>>>
  collidingEntities(const std::vector<std::shared_ptr<Entity>> &entities) {
    update(entities);
    std::vector<std::tuple<std::shared_ptr<Entity>, std::shared_ptr<Entity>>>
      collidingEntities;
    for (auto const &imap : entitiesByCell) {

      for (auto it1 = imap.second.begin(); it1 != imap.second.end(); ++it1) {
        for (auto it2 = std::next(it1); it2 != imap.second.end(); ++it2) {
          if (areColliding(*it1, *it2)) {
            collidingEntities.push_back(std::make_tuple(*it1, *it2));
          }
        }
      }
    }
    return collidingEntities;
  }

  private:
  void update(const std::vector<std::shared_ptr<Entity>> &entities) {

    for (auto const &imap : entitiesByCell) {
      entitiesByCell[imap.first] = std::set<std::shared_ptr<Entity>>();
    }

    for (auto &entity : entities) {
      auto t = std::tuple(int(entity->position.x / cellSize) * cellSize,
                          int(entity->position.y / cellSize) * cellSize);
      entitiesByCell.at(t).insert(entity);
    }
  }
};

#endif
