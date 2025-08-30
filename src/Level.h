#pragma once
#include <vector>
#include <string>
#include "EntityType.h"

// This is the struct declared in your header
struct EntitySpawnData {
    EntityType type;
    int tileX;
    int tileY;
};

class Level {
public:
    Level(); // <-- 1. DECLARE THE CONSTRUCTOR
    bool loadFromFile(const std::string& filename);

    int getWidth() const;
    int getHeight() const;
    const std::vector<std::vector<int>>& getMapData() const;
    const std::vector<EntitySpawnData>& getEntitySpawns() const;

private:
    int width;  // <-- 2. DECLARE THE MEMBER VARIABLES
    int height; // <-- 2. DECLARE THE MEMBER VARIABLES
    std::vector<std::vector<int>> mapData;
    std::vector<EntitySpawnData> entitySpawns;
};