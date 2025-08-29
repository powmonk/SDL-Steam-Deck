#include "Enemy.h"
#include "Config.h"
#include "ShapeRenderComponent.h"
#include "PatrolAIComponent.h"
#include <memory>

void Enemy::init(int size, float x, float y) {
    tileSize = size;
    x_pos = x;
    y_pos = y;
    x_vel = 0.0f;
    y_vel = 0.0f;
    width = tileSize;
    height = tileSize;

    // Give the enemy its "brain"
    aiComponent = std::make_unique<PatrolAIComponent>();

    SDL_Color blue = {0, 0, 255, 255};
    renderComponent = std::make_unique<ShapeRenderComponent>(width, height, blue);
}

void Enemy::setPosition(float newX, float newY) {
    x_pos = newX;
    y_pos = newY;
}


void Enemy::update(const std::vector<std::vector<int>>& mapData) {
    Entity::update(mapData);

}