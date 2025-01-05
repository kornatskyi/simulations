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
  static sf::VertexArray
  createTriangleShape(const std::shared_ptr<Entity> &entity,
                      const sf::Color &color) {
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

  static sf::VertexArray
  createRectangleShape(const std::shared_ptr<Resource> &entity,
                       const sf::Color &color) {

    sf::VertexArray vertices(sf::PrimitiveType::Triangles);

    sf::Vertex topLeft, bottomLeft, topRight, bottomRight;

    sf::Vector2f position = convertToSFMLCoordinate(entity->position);

    float size = entity->radius; // Assuming radius is used to determine the
                                 // size of the square

    topLeft.position = sf::Vector2f({(position.x), (position.y)});

    topRight.position = sf::Vector2f({(position.x) + size, (position.y)});

    bottomLeft.position = sf::Vector2f({(position.x), (position.y) - size});

    bottomRight.position =
        sf::Vector2f({(position.x) + size, (position.y) - size});

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
};

#endif
