#include "TileMap.h"
#include "Level.h"

Tilemap::Tilemap() : tileSize(0) {}

void Tilemap::init(int size) {
    tileSize = size;
}

// THIS IS THE MISSING FUNCTION DEFINITION
void Tilemap::load(const std::vector<std::vector<int>>& map) {
    mapData = map;
}

const std::vector<std::vector<int>>& Tilemap::getMapData() const {
    return mapData;
}

void Tilemap::render(SDL_Renderer* renderer) {
    for (size_t row = 0; row < mapData.size(); ++row) {
        for (size_t col = 0; col < mapData[row].size(); ++col) {
            if (mapData[row][col] == 1) {
                SDL_Rect tileRect = {
                    (int)col * tileSize,
                    (int)row * tileSize,
                    tileSize,
                    tileSize
                };
                SDL_SetRenderDrawColor(renderer, 50, 200, 50, 255);
                SDL_RenderFillRect(renderer, &tileRect);
            }
        }
    }
}