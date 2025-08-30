#include "SpriteRenderComponent.h"

SpriteRenderComponent::SpriteRenderComponent(SDL_Texture* tex) : texture(tex) {
    width = 0;
    height = 0;
    if (texture) {
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    }
}

void SpriteRenderComponent::render(SDL_Renderer* renderer, int x, int y) {
    if (!texture) return;
    SDL_Rect destRect = { x, y, width, height };
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}

void SpriteRenderComponent::getDimensions(int& w, int& h) const {
    w = width;
    h = height;
}