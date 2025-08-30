#include "Tile.h"

Tile::Tile(std::unique_ptr<RenderComponent> rc) : renderComponent(std::move(rc)) {}

void Tile::render(SDL_Renderer* renderer, int x, int y) {
    if (renderComponent) {
        renderComponent->render(renderer, x, y);
    }
}