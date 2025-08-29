#pragma once
#include "AIComponent.h"

class PatrolAIComponent : public AIComponent {
public:
    void update(Entity& owner, const std::vector<std::vector<int>>& mapData) override;
private:
    int moveDirection = 1; // 1 for right, -1 for left
};