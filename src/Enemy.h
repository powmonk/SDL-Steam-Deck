#pragma once
#include "Entity.h"

class Enemy : public Entity {
public:
    void init(int tileSize, float x, float y) override;
    void update(const std::vector<std::vector<int>>& mapData) override;
    void setPosition(float newX, float newY) override;

};