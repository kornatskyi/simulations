#pragma once

#include <iostream>
#include <memory>

#include "Entity.h"

class Carnivore : public Entity {
public:
  Carnivore(Environment *env = nullptr);
  void interact(std::shared_ptr<Entity> other) override;
  std::shared_ptr<Entity> reproduce() override;
  void moveForward(float elapsedTime) override;
  EntityType getType() const override;
  void die() override;

private:
  float lifetime = Config::getInstance().entityMaxLifetime;
};
