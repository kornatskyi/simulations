#include "DrawablePhysics.h"

// Constructor
DrawablePhysics::DrawablePhysics(std::shared_ptr<Physics> physics)
    : physics(physics) {}

// Draw method to visualize the physics grid
void DrawablePhysics::draw(sf::RenderTarget &target,
                           sf::RenderStates states) const {
  auto cells = physics->getCells();

  for (auto &[i, j] : cells) {
    sf::RectangleShape rect(
        sf::Vector2f(physics->getCellSize(), physics->getCellSize()));
    rect.setPosition({i * physics->getCellSize(),
                      j * physics->getCellSize() + physics->getCellSize()});
    rect.setOutlineColor(sf::Color::Red);
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineThickness(1);
    target.draw(rect, states);
  }
}
