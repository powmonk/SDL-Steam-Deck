#pragma once
#include <vector>

// Forward declare Entity to avoid circular dependency
class Entity;

// Abstract base class for AI behaviors
class AIComponent {
public:
    virtual ~AIComponent() = default;
    virtual void update(Entity& owner, const std::vector<std::vector<int>>& mapData) = 0;
};