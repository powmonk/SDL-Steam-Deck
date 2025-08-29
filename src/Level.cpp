#include "Level.h"
#include <fstream>
#include <iostream>
#include <sstream>


bool Level::loadFromFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open level file: " << filepath << std::endl;
        return false;
    }

    mapData.clear();
    entitySpawns.clear();

    std::string line;
    bool readingEntities = false; // A flag to switch between parsing tiles and entities

    while (std::getline(file, line)) {
        if (line == "---ENTITIES---") {
            readingEntities = true;
            continue; // Move to the next line
        }

        if (!readingEntities) {
            // --- TILE PARSING LOGIC ---
            std::vector<int> row;
            for (char c : line) {
                if (c == '1') {
                    row.push_back(1);
                } else {
                    row.push_back(0);
                }
            }
            mapData.push_back(row);
        } else {
            // --- ENTITY PARSING LOGIC ---
            std::stringstream ss(line);
            std::string typeStr;
            int tileX, tileY;

            ss >> typeStr >> tileX >> tileY;

            EntitySpawnData spawnData;
            spawnData.tileX = tileX;
            spawnData.tileY = tileY;

            // Convert string to EntityType enum
            if (typeStr == "PLAYER") {
                spawnData.type = EntityType::Player;
            } else if (typeStr == "ENEMY") {
                spawnData.type = EntityType::BasicEnemy;
            } else {
                continue; // Skip unknown types
            }
            entitySpawns.push_back(spawnData);
        }
    }

    file.close();
    return true;
}

// Add the definition for the new getter function
const std::vector<EntitySpawnData>& Level::getEntitySpawns() const {
    return entitySpawns;
}

const std::vector<std::vector<int>>& Level::getMapData() const {
    return mapData;
}

int Level::getWidth() const {
    return mapData.empty() ? 0 : mapData[0].size();
}

int Level::getHeight() const {
    return mapData.size();
}
