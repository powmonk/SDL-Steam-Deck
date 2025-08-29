#include "Camera.h"
#include <algorithm> // For std::max and std::min

// The constructor is simple, as dimensions are set later in Game::init.
Camera::Camera() : viewport({0, 0, 0, 0}) {}

// This function sets the camera's dimensions after they've been calculated in Game::init.
void Camera::setDimensions(int w, int h) {
    viewport.w = w;
    viewport.h = h;
}

// This function contains the logic to follow the target entity and stay within the level boundaries.
void Camera::update(const Entity* target, int levelWidth, int levelHeight) {
    if (!target) {
        return;
    }

    SDL_Rect targetBox = target->getBoundingBox();

    // Center the camera on the target
    viewport.x = (targetBox.x + targetBox.w / 2) - viewport.w / 2;
    viewport.y = (targetBox.y + targetBox.h / 2) - viewport.h / 2;

    // Clamp the camera to the level boundaries to prevent it from showing empty space
    // Clamp X
    viewport.x = std::max(0, viewport.x); // Don't go past the left edge
    viewport.x = std::min(viewport.x, levelWidth - viewport.w); // Don't go past the right edge

    // Clamp Y
    viewport.y = std::max(0, viewport.y); // Don't go past the top edge
    viewport.y = std::min(viewport.y, levelHeight - viewport.h); // Don't go past the bottom edge
}