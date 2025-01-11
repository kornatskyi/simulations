#pragma once
#include <string>

class Config {
public:
  static Config &getInstance();

  // general config
  int width;
  int height;
  std::string title;

  // utils
  bool drawBoundary;
  bool drawPhysics;

  // entity and environemnt related
  int defaultSeed;
  bool genRandomEntities;
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
  Config();
};
