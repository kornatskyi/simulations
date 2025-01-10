#include "EnvConfig.h"
#include <fstream>
#include <iostream>

EnvConfig &EnvConfig::getInstance() {
  static EnvConfig instance;
  return instance;
}

EnvConfig::EnvConfig() { loadDefaults(); }

void EnvConfig::loadDefaults() {
  entityRadius = 20;
  entitySpeed = 70;
  entityEnergy = 10;
  entityMaxLifetime = 60;
  entityMaxEnergyCapacity = 10;
  energyToSplit = 10;

  spatialCellSize = 0.5 * entityRadius;
}

void EnvConfig::loadFromFile(const std::string &filename) {
  // implement when needed
}
