#include "Player.h"
#include "Config.h"
#include "ShapeRenderComponent.h" // <-- Make sure this is included
#include <memory>                 // <-- Make sure this is included


void Player::init(int size, float x, float y) {
    tileSize = size;
    x_pos = x;
    y_pos = y;
    x_vel = 0.0f;
    y_vel = 0.0f;
    width = tileSize;
    height = tileSize * 1.5f;

    // Player must create its own RenderComponent
    SDL_Color red = {255, 0, 0, 255};
    renderComponent = std::make_unique<ShapeRenderComponent>(width, height, red);

}

void Player::setPosition(float newX, float newY) {
    x_pos = newX;
    y_pos = newY;
}


bool Player::isInvincible() const {
    return invincibilityTimer > 0;
}

void Player::handleInput(const SDL_Event& event) {
    // --- Keyboard Input ---
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        const bool isKeyDown = (event.type == SDL_KEYDOWN);
        switch (event.key.keysym.sym) {
            case SDLK_w: case SDLK_UP: case SDLK_SPACE:
                moveUp = isKeyDown;
                break;
            case SDLK_a: case SDLK_LEFT:
                moveLeft = isKeyDown;
                break;
            case SDLK_d: case SDLK_RIGHT:
                moveRight = isKeyDown;
                break;
        }
    }

    // --- Controller Button Input ---
    if (event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERBUTTONUP) {
        const bool isButtonDown = (event.type == SDL_CONTROLLERBUTTONDOWN);
        switch (event.cbutton.button) {
            case SDL_CONTROLLER_BUTTON_A: // The 'A' button for jumping
            case SDL_CONTROLLER_BUTTON_DPAD_UP:
                moveUp = isButtonDown;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                moveLeft = isButtonDown;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                moveRight = isButtonDown;
                break;
        }
    }

    // --- Controller Analog Stick Input ---
    if (event.type == SDL_CONTROLLERAXISMOTION) {
        // Handle the left analog stick's X-axis
        if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
            const int DEAD_ZONE = 8000; // Prevents stick drift

            if (event.caxis.value < -DEAD_ZONE) {
                moveLeft = true;
                moveRight = false;
            } else if (event.caxis.value > DEAD_ZONE) {
                moveLeft = false;
                moveRight = true;
            } else {
                moveLeft = false;
                moveRight = false;
            }
        }
    }
}

void Player::update(const std::vector<std::vector<int>>& mapData) {
    // Countdown the invincibility timer each frame
    if (invincibilityTimer > 0) {
        invincibilityTimer--;
    }

    // 1. Handle player-specific logic (input)
    // Only allow player input if not being knocked back
    if (invincibilityTimer == 0) {
        x_vel = 0;
        if (moveLeft) x_vel -= GameConfig::PLAYER_SPEED;
        if (moveRight) x_vel += GameConfig::PLAYER_SPEED;

        if (moveUp && isOnGround) {
            y_vel = -GameConfig::JUMP_FORCE;
            isOnGround = false;
        }
    }

    // 2. Apply generic physics (gravity)
    if (!isOnGround) {
        y_vel += GameConfig::GRAVITY;
    }

    // 3. Call the generic collision handler
    handleCollisions(mapData);
}

// --- ADD THE NEW takeDamage METHOD ---
void Player::takeDamage(const Entity* other) {
    // If we're already invincible, do nothing
    if (invincibilityTimer > 0) {
        return;
    }

    // Set the invincibility timer (e.g., 90 frames = 1.5 seconds at 60fps)
    invincibilityTimer = 90;

    // --- KNOCKBACK LOGIC ---
    // Get the center of the player and the other entity
    float playerCenterX = x_pos + width / 2;
    float otherCenterX = other->getBoundingBox().x + other->getBoundingBox().w / 2;

    // Apply knockback away from the other entity
    if (playerCenterX < otherCenterX) {
        // Player is on the left, knock them left
        x_vel = -GameConfig::PLAYER_SPEED;
    } else {
        // Player is on the right, knock them right
        x_vel = GameConfig::PLAYER_SPEED;
    }

    // Apply a small upward jump
    y_vel = -GameConfig::JUMP_FORCE / 2.0f;
    isOnGround = false;
}
