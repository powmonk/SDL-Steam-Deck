#include "Enemy.h"
#include "Config.h"
#include "ShapeRenderComponent.h"
#include "PatrolAIComponent.h"
#include <memory>

void Enemy::init(float x, float y, int TILE_SIZE) {
    x_pos = x;
    y_pos = y;
    x_vel = 0.0f;
    y_vel = 0.0f;
    this->tileSize = TILE_SIZE;
    aiComponent = std::make_unique<PatrolAIComponent>(); // <-- Add this line

}

void Enemy::setPosition(float newX, float newY) {
    x_pos = newX;
    y_pos = newY;
}


void Enemy::update(const std::vector<std::vector<int>>& mapData) {
    Entity::update(mapData);

}