//
// Created by capn on 8/29/25.
//

#pragma once
#include <SDL2/SDL.h>
#include "Entity.h"

class Camera {
public:
    Camera();
    void setDimensions(int w, int h); // <-- Add this method

    // Updates the camera's position to follow the target entity
    void update(const Entity* target, int levelWidth, int levelHeight);

    // Getters for the camera's position
    int getX() const { return viewport.x; }
    int getY() const { return viewport.y; }

private:
    SDL_Rect viewport;
};