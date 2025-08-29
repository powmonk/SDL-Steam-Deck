#include "Player.h"

void Player::init(SDL_Renderer* ren, int size, float x, float y) {
    renderer = ren;
    tileSize = size;
    x_pos = x;
    y_pos = y;
    x_vel = 0.0f;
    y_vel = 0.0f;
    width = tileSize;
    height = tileSize * 1.5f;
}

void Player::handleInput(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        const bool isKeyDown = (event.type == SDL_KEYDOWN);
        switch (event.key.keysym.sym) {
            case SDLK_w: case SDLK_UP: case SDLK_SPACE: moveUp = isKeyDown; break;
            case SDLK_a: case SDLK_LEFT: moveLeft = isKeyDown; break;
            case SDLK_d: case SDLK_RIGHT: moveRight = isKeyDown; break;
        }
    }
}

void Player::update(const std::vector<std::vector<int>>& mapData) {
    // 1. Handle player-specific logic (input)
    x_vel = 0;
    if (moveLeft) x_vel -= PLAYER_SPEED;
    if (moveRight) x_vel += PLAYER_SPEED;

    if (moveUp && isOnGround) {
        y_vel = -JUMP_FORCE;
        isOnGround = false;
    }

    // 2. Apply generic physics (gravity)
    y_vel += GRAVITY;

    // 3. Call the generic collision handler from the base Entity class
    handleCollisions(mapData);
}

void Player::render() {
    rect = { static_cast<int>(x_pos), static_cast<int>(y_pos), static_cast<int>(width), static_cast<int>(height) };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
    SDL_RenderFillRect(renderer, &rect);
}