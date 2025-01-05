// Config.h
#pragma once

namespace Config {
// General
constexpr int WIDTH = 1600;
constexpr int HEIGHT = 900;
constexpr char TITLE[] = "Predator/pray simulation.";

// Seeds
constexpr int defaultSeed = 42;

inline bool drawBoundary = true;
inline bool drawPhysics = false;
} // namespace Config
