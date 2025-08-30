#pragma once
#include "Entity.h" // Include the base class
#include <SDL2/SDL.h> // Needed for SDL_Texture


// Player "is an" Entity
class Player : public Entity {
public:
    //void init(int tileSize, float x, float y) override;
    //Sprite Based rendering
    void init(float x, float y, int tileSize) override;
    void update(const std::vector<std::vector<int>>& mapData) override;
    void handleInput(const SDL_Event& event) override;
    void takeDamage(const Entity* other);
    bool isInvincible() const;
    void setPosition(float newX, float newY) override;

private:
    // Player-specific state
    bool moveUp = false;
    bool moveLeft = false;
    bool moveRight = false;
    int invincibilityTimer = 0;
};
