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

  entityRadius = 20;
  entitySpeed = 70;
  entityEnergy = 10;
  entityMaxLifetime = 60;
  entityMaxEnergyCapacity = 10;
  energyToSplit = 10;

  spatialCellSize = 2.5 * entityRadius;
}

void Config::loadFromFile(const std::string &filename) {
  // implement when needed
}
