#include "TileMap.h"
#include "Level.h"
#include "Config.h"


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

void Tilemap::render(SDL_Renderer* renderer, int cameraX, int cameraY, int logicalWidth) {
    // Calculate which tiles are visible on screen
    int startCol = cameraX / tileSize;
    int endCol = (cameraX + logicalWidth) / tileSize;
    int startRow = cameraY / tileSize;
    int endRow = (cameraY + GameConfig::FIXED_LOGICAL_HEIGHT) / tileSize;

    // Clamp the values to the map dimensions
    startCol = std::max(0, startCol);
    endCol = std::min(endCol + 1, (int)mapData[0].size());
    startRow = std::max(0, startRow);
    endRow = std::min(endRow + 1, (int)mapData.size());

    for (int row = startRow; row < endRow; ++row) {
        for (int col = startCol; col < endCol; ++col) {
            if (mapData[row][col] == 1) {
                SDL_Rect tileRect = {
                    (col * tileSize) - cameraX, // Apply camera offset
                    (row * tileSize) - cameraY, // Apply camera offset
                    tileSize,
                    tileSize
                };
                SDL_SetRenderDrawColor(renderer, 50, 200, 50, 255);
                SDL_RenderFillRect(renderer, &tileRect);
            }
        }
    }
}