#pragma once
#include <vector>
#include <string>
#include "EntityType.h"

// A simple struct to hold the data for spawning one entity
struct EntitySpawnData {
    EntityType type;
    int tileX;
    int tileY;
};

class Level {
public:
    bool loadFromFile(const std::string& filepath);

    const std::vector<std::vector<int>>& getMapData() const;

    // New getter for the entity spawn data
    const std::vector<EntitySpawnData>& getEntitySpawns() const;

    int getWidth() const;
    int getHeight() const;

private:
    std::vector<std::vector<int>> mapData;
    std::vector<EntitySpawnData> entitySpawns;
};