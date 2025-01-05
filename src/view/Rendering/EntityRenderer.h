#ifndef ENTITYRENDERER_HEADER
#define ENTITYRENDERER_HEADER

#include <SFML/Graphics.hpp>
#include <memory>
#include <model/Entity/Entity.h>
#include <model/Entity/Resource.h>
#include <vector>

class EntityRenderer {
public:
  static sf::VertexArray createShape(const std::shared_ptr<Entity> &entity,
                                     const sf::Color &color);

  static sf::Color determineColor(EntityType type);

private:
  static sf::VertexArray
  createTriangleShape(const std::shared_ptr<Entity> &entity,
                      const sf::Color &color);

  static sf::VertexArray
  createRectangleShape(const std::shared_ptr<Resource> &entity,
                       const sf::Color &color);
};

#endif // ENTITYRENDERER_HEADER
