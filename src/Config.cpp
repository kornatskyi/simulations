#include "Config.h"
#include <fstream>
#include <iostream>

Config &Config::getInstance() {
  static Config instance;
  return instance;
}

Config::Config() { loadDefaults(); }

void Config::loadDefaults() {
  width = 1600;
  height = 900;
  title = "Predator/prey simulation.";
  defaultSeed = 42;
  drawBoundary = true;
  drawPhysics = true;
  genRandomEntities = true;
}

void Config::loadFromFile(const std::string &filename) {
  // implement when needed
}
