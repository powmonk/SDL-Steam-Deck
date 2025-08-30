#pragma once
#include "RenderComponent.h"
#include <SDL2/SDL_image.h>

class ShapeRenderComponent : public RenderComponent { // <-- FIX THIS NAME
public:
    ShapeRenderComponent(int w, int h, SDL_Color color);
    void render(SDL_Renderer* renderer, int x, int y) override;


private:
    int width;
    int height;
    SDL_Color drawColor;
};