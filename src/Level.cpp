#include "Level.h"
#include <fstream>
#include <iostream>

bool Level::loadFromFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open level file: " << filepath << std::endl;
        return false;
    }

    mapData.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> row;
        for (char c : line) {
            if (c == '1') {
                row.push_back(1);
            } else {
                row.push_back(0);
            }
        }
        mapData.push_back(row);
    }

    file.close();
    return true;
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
