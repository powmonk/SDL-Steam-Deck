#include "TileMap.h"
#include "Config.h"
#include "SpriteRenderComponent.h"
#include "ShapeRenderComponent.h"
#include <iostream>

Tilemap::Tilemap() : tileSize(0), mTile1Texture(nullptr), mTile2Texture(nullptr) {}

void Tilemap::init(int size, SDL_Texture* tile1Texture, SDL_Texture* tile2Texture) {
    tileSize = size;
    mTile1Texture = tile1Texture;
    mTile2Texture = tile2Texture;
}

void Tilemap::load(const std::vector<std::vector<int>>& map) {
    mapData = map;
    tileObjects.clear();
    tileObjects.resize(map.size());

    for (int row = 0; row < map.size(); ++row) {
        tileObjects[row].resize(map[row].size());
        for (int col = 0; col < map[row].size(); ++col) {
            int tileType = map[row][col];
            if (tileType == 0) {
                continue; // Skip empty tiles, leaving them as nullptr
            }

            std::unique_ptr<RenderComponent> renderComp = nullptr;
            SDL_Texture* textureToUse = nullptr;

            // Determine which texture to use based on the tile type
            switch (tileType) {
                case 1:
                    textureToUse = mTile1Texture;
                    textureToUse = mTile2Texture;
                    break;
                case 2:
                    //textureToUse = mTile3Texture;
                    break;
                default:
                    // This will catch any unexpected tile numbers in your map file.
                    std::cout << "Warning: Unknown tile type '" << tileType << "' at (" << col << "," << row << "). Using fallback." << std::endl;
                    break;
            }

            // --- THIS IS THE FIX ---
            // First, check if we have a valid texture. If so, use it.
            if (textureToUse) {
                renderComp = std::make_unique<SpriteRenderComponent>(textureToUse);
            }
            // If there's NO texture, ALWAYS create a visible fallback shape.
            else {
                SDL_Color fallbackColor;
                switch (tileType) {
                    case 1:
                        fallbackColor = {50, 50, 50, 255}; // Dark grey for tile 1
                        break;
                    case 2:
                        fallbackColor = {100, 50, 50, 255}; // Dark red for tile 2
                        break;
                    default:
                        fallbackColor = {255, 0, 255, 255}; // Bright magenta for unknown tiles
                        break;
                }
                renderComp = std::make_unique<ShapeRenderComponent>(tileSize, tileSize, fallbackColor);
            }

            // Create the Tile object with the guaranteed valid RenderComponent
            tileObjects[row][col] = std::make_unique<Tile>(std::move(renderComp));
        }
    }
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
            // Check if the tile object exists before rendering
            if (tileObjects[row][col]) {
                tileObjects[row][col]->render(renderer, (col * tileSize) - cameraX, (row * tileSize) - cameraY);
            }
        }
    }
}