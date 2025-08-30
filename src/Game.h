#pragma once
#include <vector>
#include <memory> // For std::unique_ptr
#include "Entity.h"
#include "TileMap.h"
#include "Player.h"
#include "Level.h"
#include "Camera.h"
#include <SDL2/SDL_image.h> // <-- Add this include



class Game {
public:
    Game();
    ~Game();

    void run(); // This will contain the main game loop

private:
    void init();
    void handleEvents();
    void update();
    void render();
    void clean();

    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_GameController* gameController;
    int tileSize;
    Level level;
    Tilemap tilemap;
    /// A list to hold all entities in the game
    std::vector<std::unique_ptr<Entity>> entities;
    Camera camera;
    // Store the calculated logical dimensions
    int mLogicalWidth;
    int mLogicalHeight;
    //Textures for entities
    SDL_Texture* mPlayerTexture = nullptr; // <-- Add texture members
    SDL_Texture* mEnemyTexture = nullptr;  // <-- Initialize to nullptr
    SDL_Texture* mTile1Texture = nullptr; // <-- Add this
    SDL_Texture* mTile2Texture = nullptr; // <-- Add this
};

