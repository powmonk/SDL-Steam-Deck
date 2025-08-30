//
// Created by capn on 8/29/25.
//

#include "Entity.h"
#include "Config.h" // <-- ADD THIS

void Entity::setVelocity(float vx, float vy) {
    x_vel = vx;
    y_vel = vy;
}

SDL_FPoint Entity::getVelocity() const {
    return {x_vel, y_vel};
}

SDL_Rect Entity::getBoundingBox() const {
    return {(int)x_pos, (int)y_pos, (int)width, (int)height};
}

// This function is moved from Player and is now generic
void Entity::handleCollisions(const std::vector<std::vector<int>>& mapData) {
    const int mapHeight = mapData.size();
    if (mapHeight == 0) return;
    const int mapWidth = mapData[0].size();

    // --- Horizontal Collision ---
    x_pos += x_vel;
    int left_tile = x_pos / tileSize;
    // FIX 1: Check the pixel just INSIDE the right edge
    int right_tile = (x_pos + width - 1) / tileSize;
    int top_tile = y_pos / tileSize;
    // FIX 2: Check the pixel just INSIDE the bottom edge
    int bottom_tile = (y_pos + height - 1) / tileSize;

    for (int row = top_tile; row <= bottom_tile; ++row) { // Also, use <= here to check the bottom row
        if (row < 0 || row >= mapHeight) continue;

        // Boundary checks (no change)
        if (right_tile >= mapWidth) { x_pos = mapWidth * tileSize - width; break; }
        if (left_tile < 0) { x_pos = 0; break; }

        if (x_vel > 0) { // Moving right
            if (mapData[row][right_tile] == 1) {
                x_pos = right_tile * tileSize - width;
                x_vel = 0; // Stop horizontal movement on collision
                break;
            }
        } else if (x_vel < 0) { // Moving left
            if (mapData[row][left_tile] == 1) {
                x_pos = (left_tile + 1) * tileSize;
                x_vel = 0; // Stop horizontal movement on collision
                break;
            }
        }
    }

    // --- Vertical Collision ---
    y_pos += y_vel;
    isOnGround = false;
    left_tile = x_pos / tileSize;
    // FIX 3: Re-calculate with the corrected horizontal position and the -1 fix
    right_tile = (x_pos + width - 1) / tileSize;
    top_tile = y_pos / tileSize;
    // FIX 4: Re-calculate with the -1 fix
    bottom_tile = (y_pos + height - 1) / tileSize;

    for (int col = left_tile; col <= right_tile; ++col) {
        if (col < 0 || col >= mapWidth) continue;

        // Boundary checks (no change)
        if (bottom_tile >= mapHeight) { y_pos = mapHeight * tileSize - height; isOnGround = true; break; }
        if (top_tile < 0) { y_pos = 0; y_vel = 0; break; }

        if (y_vel > 0) { // Moving down
            if (mapData[bottom_tile][col] == 1) {
                y_pos = bottom_tile * tileSize - height;
                y_vel = 0;
                isOnGround = true;
                break;
            }
        } else if (y_vel < 0) { // Moving up
            if (mapData[top_tile][col] == 1) {
                y_pos = (top_tile + 1) * tileSize;
                y_vel = 0;
                break;
            }
        }
    }
}

void Entity::setPosition(float newX, float newY) {
    x_pos = newX;
    y_pos = newY;
}

// UPDATE the base update function to run the AI and physics
void Entity::update(const std::vector<std::vector<int>>& mapData) {
    // 1. Let the AI component do its thinking
    if (aiComponent) {
        aiComponent->update(*this, mapData);
    }

    // 2. Apply physics
    if (!isOnGround) {
        y_vel += GameConfig::GRAVITY;
    }
    handleCollisions(mapData);
}