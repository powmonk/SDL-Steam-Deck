#include "PatrolAIComponent.h"
#include "Entity.h"   // Include the full Entity definition here
#include "Config.h"
#include <memory>

void PatrolAIComponent::update(Entity& owner, const std::vector<std::vector<int>>& mapData) {
    auto box = owner.getBoundingBox();
    int tileSize = owner.getTileSize();

    int left_tile = box.x / tileSize;
    int right_tile = (box.x + box.w) / tileSize;
    int bottom_tile = (box.y + box.h) / tileSize;

    int lookahead_col = (moveDirection > 0) ? right_tile + 1 : left_tile - 1;
    bool shouldTurn = false;

    // Wall Detection
    if (bottom_tile > 0 && lookahead_col >= 0 && lookahead_col < mapData[0].size()) {
        if (mapData[bottom_tile - 1][lookahead_col] == 1) {
            shouldTurn = true;
        }
    }

    // Ledge Detection
    if (!shouldTurn) {
        if (lookahead_col >= 0 && lookahead_col < mapData[0].size() && bottom_tile + 1 < mapData.size()) {
            if (mapData[bottom_tile + 1][lookahead_col] == 0) {
                shouldTurn = true;
            }
        } else {
            shouldTurn = true;
        }
    }
    
    if (shouldTurn) {
        moveDirection *= -1;
    }
    
    // The component tells its owner how to move
    owner.setVelocity(GameConfig::ENEMY_SPEED * moveDirection, owner.getVelocity().y);
}