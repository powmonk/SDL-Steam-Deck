#pragma once
#include "RenderComponent.h"
#include <SDL2/SDL_image.h>

class SpriteRenderComponent : public RenderComponent {
public:
    SpriteRenderComponent(SDL_Texture* tex); // <-- Correct constructor
    void render(SDL_Renderer* renderer, int x, int y) override;

    void getDimensions(int& w, int& h) const; // <-- Add this method

private:
    SDL_Texture* texture;
    int width;
    int height;
};