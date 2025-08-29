//
// Created by capn on 8/29/25.
//

#pragma once
#include <SDL2/SDL.h>
#include <vector>

// These constants are now relevant to all entities
const float GRAVITY = 0.5f;

class Entity {
public:
    virtual ~Entity() = default; // Virtual destructor for base class

    // Pure virtual functions that derived classes MUST implement
    virtual void init(SDL_Renderer* renderer, int tileSize, float x, float y) = 0;
    virtual void update(const std::vector<std::vector<int>>& mapData) = 0;
    virtual void render() = 0;

    // New virtual function for input handling.
    // Default implementation does nothing.
    virtual void handleInput(const SDL_Event& event) {} //

protected: // Accessible by derived classes (Player, Enemy)
    void handleCollisions(const std::vector<std::vector<int>>& mapData);

    SDL_Rect rect;
    SDL_Renderer* renderer;

    float x_pos, y_pos;
    float x_vel, y_vel;
    float width, height;

    bool isOnGround = false;
    int tileSize;
};
