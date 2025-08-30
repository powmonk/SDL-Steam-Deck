#include "Game.h"
#include "Level.h"
#include "Player.h" // Needed to create a Player instance
#include "Enemy.h"
#include "Config.h"
#include "EntityFactory.h"
#include "EntityType.h"
#include "Camera.h"
#include <iostream>
#include <SDL2/SDL_image.h> // <-- Add this include


// A helper function for AABB collision check
bool checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    // The sides of the rectangles
    int leftA = a.x;
    int rightA = a.x + a.w;
    int topA = a.y;
    int bottomA = a.y + a.h;

    int leftB = b.x;
    int rightB = b.x + b.w;
    int topB = b.y;
    int bottomB = b.y + b.h;

    // If any of the sides from A are outside of B
    if (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB) {
        return false;
    }

    return true;
}

Game::Game() :
isRunning(false),
  window(nullptr),
  renderer(nullptr),
  gameController(nullptr),
  tileSize(0),
  camera(),
  mLogicalWidth(0),
  mLogicalHeight(0)
{}

Game::~Game() {
    clean();
}

void Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
    // --- Add SDL_image initialization ---
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0) { /* ... */ }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout << "SDL_image could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
        // Don't return, we can fall back to shapes!
    }

    SDL_DisplayMode displayMode;
    SDL_GetDesktopDisplayMode(0, &displayMode);

    window = SDL_CreateWindow("Platformer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              displayMode.w, displayMode.h, SDL_WINDOW_FULLSCREEN);
    if (!window) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return;
    }

    // --- ASPECT RATIO CALCULATION ---
    float aspectRatio = (float)displayMode.w / (float)displayMode.h;
    mLogicalHeight = GameConfig::FIXED_LOGICAL_HEIGHT; // Use the new constant name
    mLogicalWidth = (int)(mLogicalHeight * aspectRatio);

    // Set the logical size using the variables we just calculated
    SDL_RenderSetLogicalSize(renderer, mLogicalWidth, mLogicalHeight);

    camera.setDimensions(mLogicalWidth, mLogicalHeight);

    // --- Load Textures ---
    // Place sprites in an "assets" folder. If a file doesn't exist, IMG_LoadTexture returns nullptr,
    // and your fallback system will automatically take over.
    mPlayerTexture = IMG_LoadTexture(renderer, "../assets/player.png");
    if (!mPlayerTexture) std::cout << "Warning: Could not load player texture. Using fallback shape." << std::endl;

    mEnemyTexture = IMG_LoadTexture(renderer, "../assets/enemy.png");
    if (!mEnemyTexture) std::cout << "Warning: Could not load enemy texture. Using fallback shape." << std::endl;


    if (!level.loadFromFile("../src/Maps/00.txt")) {
        isRunning = false;
        return;
    }

    // Calculate tile size using the new variable
    tileSize = GameConfig::TILE_SIZE; // Use the reliable constant

    tilemap.init(tileSize);
    tilemap.load(level.getMapData());

    /// --- MODIFIED Entity Creation Loop ---
    const auto& spawns = level.getEntitySpawns();
    for (const auto& spawnData : spawns) {
        float pixelX = spawnData.tileX * tileSize;
        float pixelY = spawnData.tileY * tileSize;

        // Pass the (possibly nullptr) textures to the factory
        auto entity = EntityFactory::create(spawnData.type, pixelX, pixelY, tileSize, mPlayerTexture, mEnemyTexture);

        if (entity) {
            entities.push_back(std::move(entity));
        }
    }

    // Controller setup
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
        if (e.type == SDL_QUIT ||
           (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) ||
           (e.type == SDL_CONTROLLERBUTTONDOWN && e.cbutton.button == SDL_CONTROLLER_BUTTON_START))
        {
            isRunning = false;
        }

        // Polymorphically pass events to all entities
        for (auto& entity : entities) {
            entity->handleInput(e);
        }
    }
}
void Game::update() {
    // 1. Update Camera Position
    // We'll assume the first entity is the player for the camera to follow
    if (!entities.empty()) {
        int levelPixelWidth = level.getWidth() * tileSize;
        int levelPixelHeight = level.getHeight() * tileSize;
        camera.update(entities[0].get(), levelPixelWidth, levelPixelHeight);
    }

    // 2. Polymorphically update all entities
    for (auto& entity : entities) {
        entity->update(level.getMapData());
    }

    // 3. Handle Entity-vs-Entity collisions with resolution
    for (size_t i = 0; i < entities.size(); ++i) {
        for (size_t j = i + 1; j < entities.size(); ++j) {
            Entity* entityA = entities[i].get();
            Entity* entityB = entities[j].get();

            SDL_Rect boxA = entityA->getBoundingBox();
            SDL_Rect boxB = entityB->getBoundingBox();

            if (checkCollision(boxA, boxB)) {
                // --- COLLISION RESPONSE LOGIC ---

                // First, identify the player and the other entity
                Player* player = dynamic_cast<Player*>(entityA);
                Entity* other = entityB;
                if (!player) {
                    player = dynamic_cast<Player*>(entityB);
                    other = entityA;
                }

                // If this is a collision involving the player
                if (player && dynamic_cast<Enemy*>(other)) {
                    // --- A. Physical Resolution (The Push) ---
                    SDL_Rect playerBox = player->getBoundingBox();
                    SDL_Rect otherBox = other->getBoundingBox();

                    // Calculate the overlap on the X axis
                    float overlapX = std::min(playerBox.x + playerBox.w, otherBox.x + otherBox.w) - std::max(playerBox.x, otherBox.x);

                    // Find player and other centers
                    float playerCenterX = playerBox.x + playerBox.w / 2.0f;
                    float otherCenterX = otherBox.x + otherBox.w / 2.0f;

                    // Push the player out of the other entity
                    if (playerCenterX < otherCenterX) {
                        // Player is on the left, push them left
                        player->setPosition(playerBox.x - overlapX, playerBox.y);
                    } else {
                        // Player is on the right, push them right
                        player->setPosition(playerBox.x + overlapX, playerBox.y);
                    }

                    // --- B. Gameplay Logic (The Damage) ---
                    if (!player->isInvincible()) {
                        player->takeDamage(other);
                    }
                }
            }
        }
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 20, 20, 50, 255);
    SDL_RenderClear(renderer);

    int cameraX = camera.getX();
    int cameraY = camera.getY();

    // The tilemap render call doesn't change
    tilemap.render(renderer, cameraX, cameraY, mLogicalWidth);

    // --- NEW ENTITY RENDER LOOP ---
    for (auto& entity : entities) {
        RenderComponent* component = entity->getRenderComponent();
        if (component) {
            SDL_Rect box = entity->getBoundingBox();
            int screenX = box.x - cameraX;
            int screenY = box.y - cameraY;
            component->render(renderer, screenX, screenY);
        }
    }

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    // --- Clean up textures ---
    if (mPlayerTexture) SDL_DestroyTexture(mPlayerTexture);
    if (mEnemyTexture) SDL_DestroyTexture(mEnemyTexture);


    if (gameController) {
        SDL_GameControllerClose(gameController);
        gameController = nullptr;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    std::cout << "Game cleaned!" << std::endl;
}
