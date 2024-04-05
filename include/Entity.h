#include "math_utils.h"
#include "utils.h"
#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef ENTITY_HEADER
#define ENTITY_HEADER

class Entity {
  public:
    Vector2 position;
    float speed;
    float angle;

    Entity() {
        position = Vector2(0.f, 0.f);
        speed = 0.f;
        angle = 0.f;
    }
    Entity(Vector2 position, float speed, float angle)
        : position(position), speed(speed), angle(angle) {}

    void moveForward(float elapsedTime) {
        position.x = position.x + std::cos(dToR(angle)) * speed * elapsedTime;
        position.y = position.y + std::sin(dToR(angle)) * speed * elapsedTime;
    }

  private:
};

class Environment {
  public:
    Environment() {
        Entity entity(Vector2(100, -100), 10, 90);
        Entity entity2(Vector2(200, -200), 10, 45);
        Entity entity3(Vector2(500, -700), 10, 180);
        Entity entity4(Vector2(600, -700), 10, 360);
        Entity entity5(Vector2(300, -800), 10, 270);
        Entity entity6(Vector2(400, -800), 10, 30);
        entities = std::vector<Entity>{
            entity,
            entity2,
            entity3,
            entity4,
            entity5,
            entity6,
        };
    }

    std::vector<Entity> entities;

  private:
};

class DrawableEntities : public sf::Drawable {
  public:
    DrawableEntities(std::vector<Entity>& entities)
        : entities(entities) {}

    void update(float elapsedTime) {
        this->m_vertices = sf::VertexArray(sf::Triangles, 3 * entities.size());
        for (std::size_t i = 0; i < entities.size(); ++i) {
            auto& entity = entities[i];
            // Move
            entity.moveForward(elapsedTime);
            // std::cout << elapsedTime << std::endl;
            // rotate
            sf::Vector2f entityPosition = convertToSFMLCoordinate(entity.position);
            auto rotatedPoint = rotate(entityPosition.x, entityPosition.y,
                                       entityPosition.x - 10, entityPosition.y + 10,
                                       -entity.angle);
            m_vertices[3 * i + 0].position = sf::Vector2f(rotatedPoint.x, rotatedPoint.y);
            rotatedPoint = rotate(entityPosition.x, entityPosition.y, entityPosition.x - 10,
                                  entityPosition.y - 10,
                                  -entity.angle);
            m_vertices[3 * i + 1].position = sf::Vector2f(rotatedPoint.x, rotatedPoint.y);
            rotatedPoint = rotate(entityPosition.x, entityPosition.y, entityPosition.x + 20,
                                  entityPosition.y - 0,
                                  -entity.angle);
            m_vertices[3 * i + 2].position = sf::Vector2f(rotatedPoint.x, rotatedPoint.y);
            m_vertices[3 * i + 0].color = sf::Color::Red;
            m_vertices[3 * i + 1].color = sf::Color::Red;
            m_vertices[3 * i + 2].color = sf::Color::Red;
        }
    }

  private:
    std::vector<Entity> entities;
    sf::VertexArray m_vertices;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // draw the vertex array
        target.draw(m_vertices, states);
    }
};

#endif
