// SpriteRenderComponent.h
#pragma once
#include "RenderComponent.h"

// A concrete RenderComponent for drawing a sprite (texture)
class SpriteRenderComponent : public RenderComponent {
public:
    // The constructor now takes a pointer to an already-loaded texture
    SpriteRenderComponent(SDL_Texture* tex, int w, int h);

    // We still override the same render function
    void render(SDL_Renderer* renderer, int x, int y) override;

private:
    SDL_Texture* texture;
    int width;
    int height;
};