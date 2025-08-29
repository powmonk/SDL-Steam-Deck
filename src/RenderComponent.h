//
// Created by capn on 8/29/25.
//
#pragma once
#include <SDL2/SDL.h>

// Abstract base class for any component that can be rendered
class RenderComponent {
public:
    virtual ~RenderComponent() = default;

    // Renders the component at a given on-screen position
    virtual void render(SDL_Renderer* renderer, int x, int y) = 0;
};