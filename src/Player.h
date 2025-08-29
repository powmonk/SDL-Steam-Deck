#pragma once
#include "Entity.h" // Include the base class

const float PLAYER_SPEED = 5.0f;
const float JUMP_FORCE = 15.0f;

// Player "is an" Entity
class Player : public Entity {
public:
    // We override the pure virtual functions from Entity
    void init(SDL_Renderer* renderer, int tileSize, float x, float y) override;
    void update(const std::vector<std::vector<int>>& mapData) override;
    void render() override;

    // This function is unique to the Player
    void handleInput(const SDL_Event& event) override;

private:
    // Player-specific state
    bool moveUp = false;
    bool moveLeft = false;
    bool moveRight = false;
};