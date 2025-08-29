#pragma once
#include <vector>
#include <memory> // For std::unique_ptr
#include "Entity.h"
#include "TileMap.h"
#include "Player.h"
#include "Level.h"


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
    //Player* player_ptr = nullptr; // A raw pointer for easy access to the player

};