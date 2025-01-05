#ifndef ENTITYRENDERER_HEADER
#define ENTITYRENDERER_HEADER

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "../Environement/Carnivore.h"
#include "../Environement/Entity.h"
#include "../Environement/Herbivore.h"
#include "../Environement/Resource.h"
#include "../Physics/Physics.h"
#include "../utils/math_utils.h"
#include "../utils/utils.h"

class EntityRenderer {
 public:
  static sf::VertexArray createShape(const std::shared_ptr<Entity> &entity,
                                     const sf::Color &color) {
    switch (entity->getType()) {
      case EntityType::RESOURCE:
        return createRectangleShape(std::static_pointer_cast<Resource>(entity),
                                    color);
      default:
        return createTriangleShape(entity, color);
    }
  }

  static sf::Color determineColor(EntityType type) {
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

 private:
  static sf::VertexArray createTriangleShape(
      const std::shared_ptr<Entity> &entity, const sf::Color &color) {
    sf::VertexArray vertices(sf::PrimitiveType::Triangles, 3);
    sf::Vector2f position = convertToSFMLCoordinate(entity->position);
    std::array<sf::Vector2f, 3> points = {
        rotatePointAround(position,
                          sf::Vector2f(position.x - entity->radius / 2,
                                       position.y + entity->radius / 2),
                          -entity->angle),
        rotatePointAround(position,
                          sf::Vector2f(position.x - entity->radius / 2,
                                       position.y - entity->radius / 2),
                          -entity->angle),
        rotatePointAround(position,
                          sf::Vector2f(position.x + entity->radius, position.y),
                          -entity->angle)};

    for (int i = 0; i < 3; ++i) {
      vertices[i].position = points[i];
      vertices[i].color = color;
    }

    return vertices;
  }

  static sf::VertexArray createRectangleShape(
      const std::shared_ptr<Resource> &entity, const sf::Color &color) {
    sf::VertexArray vertices(sf::PrimitiveType::LineStrip, 4);
    sf::Vector2f position = convertToSFMLCoordinate(entity->position);
    float size = entity->radius;  // Assuming radius is used to determine the
                                  // size of the square

    vertices[0].position = position + sf::Vector2f(-size / 2, -size / 2);
    vertices[1].position = position + sf::Vector2f(size / 2, -size / 2);
    vertices[2].position = position + sf::Vector2f(size / 2, size / 2);
    vertices[3].position = position + sf::Vector2f(-size / 2, size / 2);

    for (int i = 0; i < 4; ++i) {
      vertices[i].color = color;
    }

    return vertices;
  }
};

#endif
