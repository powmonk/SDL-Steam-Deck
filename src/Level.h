#pragma once
#include <vector>
#include <string>

class Level {
public:
    // Tries to load map data from a text file
    bool loadFromFile(const std::string& filepath);

    // A "getter" to provide the map data to other parts of the game
    const std::vector<std::vector<int>>& getMapData() const;

    // We can also provide the dimensions
    int getWidth() const;
    int getHeight() const;

private:
    std::vector<std::vector<int>> mapData;
};
