#pragma once
#include "RenderComponent.h"
#include <memory>

class Tile {
public:
    Tile(std::unique_ptr<RenderComponent> rc);
    void render(SDL_Renderer* renderer, int x, int y);

private:
    std::unique_ptr<RenderComponent> renderComponent;
};