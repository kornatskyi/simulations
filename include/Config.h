#pragma once

#ifndef CONFIG_HEADER
#define CONFIG_HEADER
namespace Config {

// General
constexpr int WIDTH = 1600;
constexpr int HEIGHT = 900;
constexpr char TITLE[] = "Predator/pray simulation.";

// Seeds
constexpr int defaultSeed = 42;

// Drawing
bool drawBoundary = true;
bool drawPhysics = false;
} // namespace Config

#endif