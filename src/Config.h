#pragma once
#include <string>

class Config {
public:
    static Config& getInstance();
    
    int width;
    int height;
    std::string title;
    int defaultSeed;
    bool drawBoundary;
    bool drawPhysics;
    bool genRandomEntities;

    void loadFromFile(const std::string& filename);
    void loadDefaults();

private:
    Config();
};
