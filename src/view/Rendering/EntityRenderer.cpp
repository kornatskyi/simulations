#include "EntityRenderer.h"
#include <utils/math_utils.h>

// Create shape based on entity type
sf::VertexArray
EntityRenderer::createShape(const std::shared_ptr<Entity> &entity,
                            const sf::Color &color) {
  switch (entity->getType()) {
  case EntityType::RESOURCE:
    return createRectangleShape(std::static_pointer_cast<Resource>(entity),
                                color);
  default:
    return createTriangleShape(entity, color);
  }
}

// Determine entity color based on type
sf::Color EntityRenderer::determineColor(EntityType type) {
  switch (type) {
  case EntityType::CARNIVORE:
    return sf::Color::Red;
  case EntityType::HERBIVORE:
    return sf::Color::Blue;
  case EntityType::RESOURCE:
    return sf::Color::Green;
  default:
    return sf::Color::White;
  }
}

// Create a triangle shape for general entities (Carnivore/Herbivore)
sf::VertexArray
EntityRenderer::createTriangleShape(const std::shared_ptr<Entity> &entity,
                                    const sf::Color &color) {
  sf::VertexArray vertices(sf::PrimitiveType::Triangles, 3);
  sf::Vector2f position = entity->position;

  std::array<sf::Vector2f, 3> points = {
      MathUtils::rotatePointAround(
          position,
          sf::Vector2f(position.x - entity->radius / 2,
                       position.y + entity->radius / 2),
          entity->angle),
      MathUtils::rotatePointAround(
          position,
          sf::Vector2f(position.x - entity->radius / 2,
                       position.y - entity->radius / 2),
          entity->angle),
      MathUtils::rotatePointAround(
          position, sf::Vector2f(position.x + entity->radius, position.y),
          entity->angle)};

  for (int i = 0; i < 3; ++i) {
    vertices[i].position = points[i];
    vertices[i].color = color;
  }

  return vertices;
}

// Create a rectangle shape for resources
sf::VertexArray
EntityRenderer::createRectangleShape(const std::shared_ptr<Resource> &entity,
                                     const sf::Color &color) {
  sf::VertexArray vertices(sf::PrimitiveType::Triangles);

  sf::Vertex topLeft, bottomLeft, topRight, bottomRight;

  sf::Vector2f position = entity->position;
  float size = entity->radius;

  topLeft.position = position + sf::Vector2f(-size / 2, -size / 2);
  topRight.position = position + sf::Vector2f(size / 2, -size / 2);
  bottomRight.position = position + sf::Vector2f(size / 2, size / 2);
  bottomLeft.position = position + sf::Vector2f(-size / 2, size / 2);

  topLeft.color = color;
  topRight.color = color;
  bottomLeft.color = color;
  bottomRight.color = color;

  vertices.append(topLeft);
  vertices.append(bottomLeft);
  vertices.append(topRight);
  vertices.append(topRight);
  vertices.append(bottomLeft);
  vertices.append(bottomRight);

  return vertices;
}
