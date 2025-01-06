#include <SFML/Graphics.hpp>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "Config.h"
#include "model/Entity/Entity.h"
#include "model/Environment/Environment.h"
#include "view/Rendering/DrawablePhysics.h"
#include "view/Rendering/Rendering.h"
#include "view/Rendering/UI.h"

class FPSMeasurer {
public:
  // Clock for measuring FPS
  sf::Clock clock;
  float lastTime = 0;
  float currentFps = 0;
  std::string fpsToDraw = std::to_string(currentFps);
  float fpsRenderPeriod = 0;
  int numberOfRenders = 0;

  std::string calculateNewFPS() {
    currentFps = numberOfRenders /
                 (fpsRenderPeriod + clock.getElapsedTime().asSeconds());
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1) << currentFps;
    fpsToDraw = oss.str();
    fpsRenderPeriod = 0; // reset renderer period
    numberOfRenders = 0;
    return fpsToDraw;
  }
};

int main() {
  sf::RenderWindow window(
      sf::VideoMode({static_cast<unsigned int>(Config::getInstance().width),
                     static_cast<unsigned int>(Config::getInstance().height)}),
      Config::getInstance().title, sf::Style::Titlebar);
  window.setVerticalSyncEnabled(true); // sync with graphics card refresh rate
  window.setPosition(sf::Vector2i(100, 400));

  // std::shared_ptr<Environment> environment = std::make_shared<Environment>();
  std::shared_ptr<Environment> environment =
      Config::getInstance().genRandomEntities
          ? std::make_shared<Environment>(100)
          : std::make_shared<Environment>();
  DrawableEntities drawableElements(environment->entities);
  DrawablePhysics drawablePhysics(environment->physics);

  // sf::View view(sf::FloatRect(0, 0, Config::getInstance().width,
  // Config::getInstance().height)); view.zoom(2); window.setView(view); run the
  // main loop

  // Utils
  FPSMeasurer fpsMeasurer;
  UI ui(environment);

  auto fpsText =
      ui.getText("FPS: " + fpsMeasurer.fpsToDraw,
                 sf::Vector2f(Config::getInstance().width - 200, 10));

  while (window.isOpen()) {
    fpsMeasurer.clock.restart();

    // handle events
    while (const auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    environment->update(0.01);

    // draw it
    window.clear();
    window.draw(drawableElements);
    if (Config::getInstance().drawPhysics) {
      window.draw(drawablePhysics);
    }
    window.draw(ui);

    if (fpsMeasurer.fpsRenderPeriod > 1) {
      // Update FPS string value
      fpsText->setString("FPS: " + fpsMeasurer.calculateNewFPS());
    }
    window.draw(*fpsText);
    window.display();

    fpsMeasurer.fpsRenderPeriod +=
        fpsMeasurer.clock.getElapsedTime().asSeconds();
    fpsMeasurer.numberOfRenders++;
  }

  return 0;
}
