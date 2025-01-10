#include "DrawablePhysics.h"
#include <tuple>

// Constructor
DrawablePhysics::DrawablePhysics(std::shared_ptr<Physics> physics)
    : physics(physics) {}

// Draw method to visualize the physics grid
void DrawablePhysics::draw(sf::RenderTarget &target,
                           sf::RenderStates states) const {

  auto grid = physics->spatialGrid.getGrid();
  for (auto &pair : grid) {
    auto [i, j] = physics->spatialGrid.getCellIndex(pair.first);

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
