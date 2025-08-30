// SpriteRenderComponent.cpp
#include "SpriteRenderComponent.h"

SpriteRenderComponent::SpriteRenderComponent(SDL_Texture* tex, int w, int h)
    : texture(tex), width(w), height(h) {}

void SpriteRenderComponent::render(SDL_Renderer* renderer, int x, int y) {
    if (!texture) {
        return; // Don't try to render a null texture
    }

    // Create a destination rectangle at the given x, y coordinates
    SDL_Rect destRect = { x, y, width, height };

    // Copy the entire texture to the destination rectangle on the renderer
    // The 'nullptr' arguments mean "use the entire source texture"
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}