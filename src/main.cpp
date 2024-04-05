#include "../include/Entity.h"
#include "../include/Rendering.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

int main() {
  sf::Clock clock;

  sf::RenderWindow window(sf::VideoMode(1600, 900), "Predator/pray simulation.",
                          sf::Style::Titlebar);
  window.setVerticalSyncEnabled(true); // sync with graphics card refresh rate
  window.setPosition(sf::Vector2i(100, 400));

  Environment environment;
  DrawableEntities des(environment.entities);

  // run the main loop
  while (window.isOpen()) {
    // handle events
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    sf::Time elapsed = clock.getElapsedTime();
    clock.restart();
    des.update(elapsed.asSeconds());
    // draw it
    window.clear();
    window.draw(des);
    window.display();
  }

  return 0;
}