#pragma once
#include "RenderComponent.h"

// A concrete RenderComponent for drawing a solid colored rectangle
class ShapeRenderComponent : public RenderComponent {
public:
    ShapeRenderComponent(int w, int h, SDL_Color color);
    void render(SDL_Renderer* renderer, int x, int y) override;

private:
    int width;
    int height;
    SDL_Color drawColor;
};