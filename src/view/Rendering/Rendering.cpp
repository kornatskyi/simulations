#include "view/Rendering/Rendering.h"
#include "EntityRenderer.h"
#include <model/Entity/Entity.h>

// Constructor
DrawableEntities::DrawableEntities(
    const std::vector<std::shared_ptr<Entity>> &entities)
    : entities(entities), boundaryEnabled(Config::drawBoundary) {}

// Enable or disable boundary rendering
void DrawableEntities::setBoundaryEnabled(bool enabled) {
  boundaryEnabled = enabled;
}

// Draw entities and their boundaries
void DrawableEntities::draw(sf::RenderTarget &target,
                            sf::RenderStates states) const {
  updateShapes();

  for (const auto &shape : shapesToRender) {
    target.draw(shape, states);
  }

  if (boundaryEnabled) {
    drawBoundaries(target, states);
  }
}

// Update shapes to render for each entity
void DrawableEntities::updateShapes() const {
  shapesToRender.clear();
  for (const auto &entity : entities) {
    shapesToRender.push_back(EntityRenderer::createShape(
        entity, EntityRenderer::determineColor(entity->getType())));
  }
}

// Draw entity boundaries
void DrawableEntities::drawBoundaries(sf::RenderTarget &target,
                                      sf::RenderStates states) const {
  if (!boundaryEnabled)
    return;

  for (const auto &entity : entities) {
    sf::Vector2f position = entity->position;

    sf::CircleShape boundary(entity->radius);
    boundary.setPosition(
        {position.x - entity->radius, position.y - entity->radius});
    boundary.setFillColor(sf::Color::Transparent);
    boundary.setOutlineThickness(1);
    boundary.setOutlineColor(sf::Color::White);
    target.draw(boundary, states);

    sf::CircleShape center(2);
    center.setPosition({position.x - 2, position.y - 2});
    center.setFillColor(sf::Color::White);
    target.draw(center, states);
  }
}
