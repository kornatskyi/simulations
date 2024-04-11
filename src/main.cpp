#include "../include/Config.h"
#include "../include/Environement/Entity.h"
#include "../include/Environement/Environment.h"
#include "../include/Rendering/Rendering.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

int main() {
  // sf::Clock clock;
  sf::RenderWindow window(sf::VideoMode(Config::WIDTH, Config::HEIGHT),
                          Config::TITLE, sf::Style::Titlebar);
  window.setVerticalSyncEnabled(true); // sync with graphics card refresh rate
  window.setPosition(sf::Vector2i(100, 400));

  Environment environment(100);
  DrawableEntities drawableElements(environment.entities);
  DrawablePhysics drawablePhysics(environment.physics);

  // sf::View view(sf::FloatRect(0, 0, Config::WIDTH, Config::HEIGHT));
  // view.zoom(2);
  // window.setView(view);
  // run the main loop
  while (window.isOpen()) {
    // handle events
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    // sf::Time elapsed = clock.getElapsedTime();
    // clock.restart();
    // environment.update(elapsed.asSeconds());
    environment.update(0.01);

    // draw it
    window.clear();
    window.draw(drawableElements);
    window.draw(drawablePhysics);
    window.display();
  }

  return 0;
}