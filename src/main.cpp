#include "../include/Entity.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

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
        des.update();
        // draw it
        window.clear();
        window.draw(des);
        window.display();
    }

    return 0;
}