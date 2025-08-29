#pragma once
#include <SDL2/SDL.h>
#include <vector>

class Tilemap {
public:
    Tilemap();
    void init(int size);
    void load(const std::vector<std::vector<int>>& map); // Ensure this is declared
    void render(SDL_Renderer* renderer);
    const std::vector<std::vector<int>>& getMapData() const;

private:
    std::vector<std::vector<int>> mapData;
    int tileSize;
};