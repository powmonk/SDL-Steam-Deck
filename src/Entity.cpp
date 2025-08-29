//
// Created by capn on 8/29/25.
//

#include "Entity.h"

// This function is moved from Player and is now generic
void Entity::handleCollisions(const std::vector<std::vector<int>>& mapData) {
    // Get map dimensions dynamically.
    const int mapHeight = mapData.size();
    if (mapHeight == 0) return; // Don't do anything if the map is empty.
    const int mapWidth = mapData[0].size();

    // --- Horizontal Collision ---
    x_pos += x_vel;
    int left_tile = x_pos / tileSize;
    int right_tile = (x_pos + width - 1) / tileSize;
    int top_tile = y_pos / tileSize;
    int bottom_tile = (y_pos + height - 1) / tileSize;

    for (int row = top_tile; row <= bottom_tile; ++row) {
        // Use dynamic mapHeight for bounds check
        if (row < 0 || row >= mapHeight) continue; // <-- CHANGE
        if (x_vel > 0) {
            // Use dynamic mapWidth for bounds check
            if (right_tile >= mapWidth || mapData[row][right_tile] == 1) { // <-- CHANGE
                x_pos = right_tile * tileSize - width;
                break;
            }
        } else if (x_vel < 0) {
            if (left_tile < 0 || mapData[row][left_tile] == 1) {
                x_pos = (left_tile + 1) * tileSize;
                break;
            }
        }
    }

    // --- Vertical Collision ---
    y_pos += y_vel;
    isOnGround = false;
    left_tile = x_pos / tileSize;
    right_tile = (x_pos + width - 1) / tileSize;
    top_tile = y_pos / tileSize;
    bottom_tile = (y_pos + height - 1) / tileSize;

    for (int col = left_tile; col <= right_tile; ++col) {
        // Use dynamic mapWidth for bounds check
        if (col < 0 || col >= mapWidth) continue; // <-- CHANGE
        if (y_vel > 0) {
            // Use dynamic mapHeight for bounds check
            if (bottom_tile >= mapHeight || mapData[bottom_tile][col] == 1) { // <-- CHANGE
                y_pos = bottom_tile * tileSize - height;
                y_vel = 0;
                isOnGround = true;
                break;
            }
        } else if (y_vel < 0) {
            if (top_tile < 0 || mapData[top_tile][col] == 1) {
                y_pos = (top_tile + 1) * tileSize;
                y_vel = 0;
                break;
            }
        }
    }
}
