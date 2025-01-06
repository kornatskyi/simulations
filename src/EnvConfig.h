#pragma once

#include <string>

class EnvConfig {
public:
  static EnvConfig &getInstance();

  float entityRadius;
  float entitySpeed;
  float entityEnergy;
  float entityMaxLifetime;
  float entityMaxEnergyCapacity;
  float energyToSplit;
  float spatialCellSize;
  

  void loadFromFile(const std::string &filename);
  void loadDefaults();

private:
  EnvConfig();
};
