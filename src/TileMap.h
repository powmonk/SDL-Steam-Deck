#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include "Tile.h" // <-- This is the key include

class Tilemap {
public:
    Tilemap();
    void init(int size, SDL_Texture* tile1Texture, SDL_Texture* tile2Texture);
    void load(const std::vector<std::vector<int>>& map);
    void render(SDL_Renderer* renderer, int cameraX, int cameraY, int logicalWidth);
    const std::vector<std::vector<int>>& getMapData() const;

private:
    // This vector of Tiles belongs here, in the Tilemap
    std::vector<std::vector<std::unique_ptr<Tile>>> tileObjects;

    std::vector<std::vector<int>> mapData;
    int tileSize;
    SDL_Texture* mTile1Texture;
    SDL_Texture* mTile2Texture;
};