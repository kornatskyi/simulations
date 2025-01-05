#ifndef DRAWABLEPHYSICS_HEADER
#define DRAWABLEPHYSICS_HEADER

#include "../Environement/Carnivore.h"
#include "../Environement/Entity.h"
#include "../Environement/Herbivore.h"
#include "../Environement/Resource.h"
#include "../Physics/Physics.h"
#include "../utils/math_utils.h"
#include "../utils/utils.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class DrawablePhysics : public sf::Drawable {
public:
  std::shared_ptr<Physics> physics;
  DrawablePhysics(std::shared_ptr<Physics> physics) : physics(physics) {}

private:
protected:
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override {

    auto cells = physics->getCells();

    for (auto &[i, j] : cells) {
      auto rect = sf::RectangleShape(
          sf::Vector2f(physics->getCellSize(), physics->getCellSize()));
      rect.setPosition({i * physics->getCellSize(),
                        j * physics->getCellSize() + physics->getCellSize()});
      rect.setOutlineColor(sf::Color::Red);
      rect.setFillColor(sf::Color::Transparent);
      rect.setOutlineThickness(1);
      target.draw(rect, states);
    }
  }
};

#endif
