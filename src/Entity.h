#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include "RenderComponent.h"
#include "AIComponent.h" // <-- ADD THIS


class Entity {
public:
    virtual ~Entity() = default;

    virtual void init(float x, float y, int tileSize) = 0;
    virtual void update(const std::vector<std::vector<int>>& mapData) = 0;
    virtual void handleInput(const SDL_Event& event) {}

    // Getters and Setters
    RenderComponent* getRenderComponent() { return renderComponent.get(); }
    SDL_Rect getBoundingBox() const;
    virtual void setPosition(float newX, float newY); // No longer pure virtual

    virtual void setRenderComponent(std::unique_ptr<RenderComponent> component) {
        renderComponent = std::move(component);
    }
    virtual void setSize(int w, int h) {
        width = w;
        height = h;
    }

    // New methods for components to control the entity
    void setVelocity(float vx, float vy);
    SDL_FPoint getVelocity() const;
    int getTileSize() const { return tileSize; }

protected:
    void handleCollisions(const std::vector<std::vector<int>>& mapData);

    std::unique_ptr<AIComponent> aiComponent; // <-- ADD THIS

    float x_pos, y_pos;
    float x_vel, y_vel;
    bool isOnGround = false;
    int tileSize = 0;
    int width = 0;
    int height = 0;
    std::unique_ptr<RenderComponent> renderComponent;

};