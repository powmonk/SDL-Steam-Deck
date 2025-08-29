#include "ShapeRenderComponent.h"

ShapeRenderComponent::ShapeRenderComponent(int w, int h, SDL_Color color)
    : width(w), height(h), drawColor(color) {}

void ShapeRenderComponent::render(SDL_Renderer* renderer, int x, int y) {
    SDL_Rect rect = {x, y, width, height};
    SDL_SetRenderDrawColor(renderer, drawColor.r, drawColor.g, drawColor.b, drawColor.a);
    SDL_RenderFillRect(renderer, &rect);
}