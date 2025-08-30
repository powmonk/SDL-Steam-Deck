#include "Level.h"
#include "EntityType.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype> // Required for isupper()

Level::Level() : width(0), height(0) {}

// Simple getters for the level's properties
int Level::getWidth() const { return width; }
int Level::getHeight() const { return height; }
const std::vector<std::vector<int>>& Level::getMapData() const { return mapData; }
const std::vector<EntitySpawnData>& Level::getEntitySpawns() const { return entitySpawns; }

// The new loading function
bool Level::loadFromFile(const std::string& filename) {
    // Clear any previous level data
    mapData.clear();
    entitySpawns.clear();

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open level file: " << filename << std::endl;
        return false;
    }

    std::string line;
    std::vector<std::string> lines;

    // Read all lines from the file into a temporary vector
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    if (lines.empty()) {
        std::cerr << "Error: Level file is empty." << std::endl;
        return false;
    }

    // Determine level dimensions
    height = lines.size();
    width = 0;
    for(const auto& l : lines) {
        if (l.length() > width) {
            width = l.length();
        }
    }

    // Resize the main mapData vector to the correct dimensions
    mapData.resize(height, std::vector<int>(width, 0));

    // Process each character of the loaded map
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < lines[row].length(); ++col) {
            char tileChar = lines[row][col];

            // Check if the character is an uppercase letter (an entity)
            if (std::isupper(tileChar)) {
                EntitySpawnData spawn;
                spawn.tileX = col;
                spawn.tileY = row;
                bool knownEntity = true;

                switch (tileChar) {
                    case 'P':
                        spawn.type = EntityType::PLAYER;
                        break;
                    case 'E':
                        spawn.type = EntityType::ENEMY;
                        break;
                    // Add other entity types like 'G' for Goomba here
                    // case 'G':
                    //     spawn.type = EntityType::GOOMBA;
                    //     break;
                    default:
                        knownEntity = false;
                        std::cout << "Warning: Unknown entity type '" << tileChar << "' at (" << col << "," << row << ")" << std::endl;
                        break;
                }

                if (knownEntity) {
                    entitySpawns.push_back(spawn);
                }

                // Entities occupy empty space, so we place a '0' tile in the map data
                mapData[row][col] = 0;

            } else {
                // It's a regular tile
                switch (tileChar) {
                    case '#':
                    case '1':
                        mapData[row][col] = 1; // Solid tile
                        break;
                    case '2':
                        mapData[row][col] = 2; // Another solid tile type
                        break;
                    // Add other tile types here
                    default:
                        mapData[row][col] = 0; // Any other character is empty space
                        break;
                }
            }
        }
    }

    std::cout << "Level loaded successfully: " << width << "x" << height << " with " << entitySpawns.size() << " entities." << std::endl;
    return true;
}