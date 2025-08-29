#include "Game.h"
#include "Level.h"
#include "Player.h" // Needed to create a Player instance
#include <iostream>

// Define a fixed logical resolution for our game (16:9 aspect ratio)
const int LOGICAL_WIDTH = 1920;
const int LOGICAL_HEIGHT = 1080;

Game::Game() :
    isRunning(false),
    window(nullptr),
    renderer(nullptr),
    gameController(nullptr),
    tileSize(0)
{}

Game::~Game() {
    clean();
}

void Game::init() {
    // Initialize SDL subsystems
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    // Get display mode to create a fullscreen window
    SDL_DisplayMode displayMode;
    SDL_GetDesktopDisplayMode(0, &displayMode);

    window = SDL_CreateWindow("Platformer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              displayMode.w, displayMode.h, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (!window) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return;
    }

    // This tells the window to capture all keyboard input.
    SDL_SetWindowKeyboardGrab(window, SDL_TRUE);

    // Set the logical size for automatic scaling
    SDL_RenderSetLogicalSize(renderer, LOGICAL_WIDTH, LOGICAL_HEIGHT);

    // Load the level from the file
    if (!level.loadFromFile("../src/Maps/00.txt")) {
        // If the level fails to load, we can't run the game.
        isRunning = false;
        return;
    }

    // Calculate tile size based on our fixed logical height
    tileSize = LOGICAL_HEIGHT / level.getHeight();

    // Initialize the tilemap
    tilemap.init(tileSize);
    tilemap.load(level.getMapData());

    // Create the player and add it to the entities list
    auto player = std::make_unique<Player>();
    //player_ptr = player.get(); // Get a raw pointer for direct access (input handling)
    player->init(renderer, tileSize, 100.0f, 100.0f);
    entities.push_back(std::move(player));

    // In the future, you could add enemies here!
    // auto enemy = std::make_unique<Enemy>();
    // enemy->init(renderer, tileSize, 400.0f, 100.0f);
    // entities.push_back(std::move(enemy));

    // Look for and open a game controller
    for (int i = 0; i < SDL_NumJoysticks(); ++i) {
        if (SDL_IsGameController(i)) {
            gameController = SDL_GameControllerOpen(i);
            if (gameController) {
                std::cout << "Controller found: " << SDL_GameControllerName(gameController) << std::endl;
                break;
            }
        }
    }

    isRunning = true;
}

void Game::run() {
    init();

    // --- Fixed Timestep Initialization ---
    // The rate at which we want to update the game logic (e.g., 60 times per second)
    const double MS_PER_UPDATE = 9;
    // Get the initial time using SDL's high-performance counter
    double previousTime = SDL_GetTicks();
    // This variable will accumulate the time passed between frames
    double lag = 0.0;

    // --- Main Game Loop ---
    while (isRunning) {
        double currentTime = SDL_GetTicks();
        double elapsed = currentTime - previousTime;
        previousTime = currentTime;
        lag += elapsed;

        // 1. Process Input
        // We process all available input each frame
        handleEvents();

        // 2. Update Game Logic
        // We call update() in fixed steps to catch up with any accumulated lag
        while (lag >= MS_PER_UPDATE) {
            update();
            lag -= MS_PER_UPDATE;
        }

        // 3. Render
        // We render just once per frame, after the logic has been updated
        render();
    }
}
void Game::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
            isRunning = false;
        }

        // Polymorphically pass events to all entities
        for (auto& entity : entities) {
            entity->handleInput(e);
        }
    }
}
void Game::update() {
    // Polymorphically update all entities in the game
    for (auto& entity : entities) {
        entity->update(tilemap.getMapData());
    }
}

void Game::render() {
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 20, 20, 50, 255);
    SDL_RenderClear(renderer);

    // Render the world
    tilemap.render(renderer);

    // Polymorphically render all entities in the game
    for (auto& entity : entities) {
        entity->render();
    }

    // Update screen
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    if (gameController) {
        SDL_GameControllerClose(gameController);
        gameController = nullptr;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Game cleaned!" << std::endl;
}