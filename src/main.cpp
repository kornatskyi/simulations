#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

struct Vector2 {
    float x;
    float y;
    Vector2() = default;
    Vector2(float x, float y)
        : x(x), y(y) {}
};

class Entity {
  public:
    Vector2 position;
    Entity() {
        this->position = Vector2(0.0f, 0.0f);
    }
    Entity(Vector2 position) {
        this->position = position;
    }

  private:
};

class DrawableEntities : public sf::Drawable {
  public:
    DrawableEntities(std::vector<Entity>& entities) {
        m_vertices = sf::VertexArray(sf::Triangles, 3 * entities.size());
        for (std::size_t i = 0; i < entities.size(); ++i) {
            const auto& entity = entities[i];
            m_vertices[3 * i + 0].position = sf::Vector2f(entity.position.x - 5, entity.position.y + 5);
            m_vertices[3 * i + 1].position = sf::Vector2f(entity.position.x - 5, entity.position.y - 5);
            m_vertices[3 * i + 2].position = sf::Vector2f(entity.position.x + 5, entity.position.y + 5);
        }
    }

  private:
    sf::VertexArray m_vertices;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // draw the vertex array
        target.draw(m_vertices, states);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Predator/pray simulation.", sf::Style::Titlebar);
    window.setVerticalSyncEnabled(true); // sync with graphics card refresh rate
    window.setPosition(sf::Vector2i(100, 400));

    Entity entity(Vector2(100, 100));
    Entity entity2(Vector2(200, 200));
    std::vector<Entity> vec{entity, entity2};
    DrawableEntities des(vec);

    // run the main loop
    while (window.isOpen()) {
        // handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // draw it
        window.clear();
        window.draw(des);
        window.display();
    }

    return 0;
}