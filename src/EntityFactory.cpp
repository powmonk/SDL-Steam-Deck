#include "EntityFactory.h"
#include "Player.h"
#include "Enemy.h"
#include "Config.h"
#include "SpriteRenderComponent.h"
#include "ShapeRenderComponent.h"

std::unique_ptr<Entity> EntityFactory::create(
    EntityType type,
    float x,
    float y,
    int TILE_SIZE,
    SDL_Texture* playerTexture,
    SDL_Texture* enemyTexture
) {
    // 1. Declare variables to hold the unique properties of the entity we're creating.
    std::unique_ptr<Entity> entity;
    SDL_Texture* textureToUse = nullptr;
    int fallbackWidth = 0;
    int fallbackHeight = 0;
    SDL_Color fallbackColor = {0, 0, 0, 0};

    // 2. Use the switch statement ONLY to set these unique properties.
    switch (type) {
        case EntityType::PLAYER:
            entity = std::make_unique<Player>();
            textureToUse = playerTexture;
            fallbackWidth = GameConfig::PLAYER_WIDTH;
            fallbackHeight = GameConfig::PLAYER_HEIGHT;
            fallbackColor = {255, 0, 0, 255};
            break;

        case EntityType::ENEMY:
            entity = std::make_unique<Enemy>();
            textureToUse = enemyTexture;
            fallbackWidth = GameConfig::ENEMY_WIDTH;
            fallbackHeight = GameConfig::ENEMY_HEIGHT;
            fallbackColor = {0, 0, 255, 255};
            break;

        // To add a new entity type, you just add another simple case here.
    }

    // 3. Now, perform the shared logic once, using the variables we just set.
    if (entity) {
        entity->init(x, y, TILE_SIZE); // The simplified init method

        std::unique_ptr<RenderComponent> renderComp = nullptr;
        int width = 0;
        int height = 0;

        if (textureToUse) {
            // Texture exists: use it.
            auto spriteComp = std::make_unique<SpriteRenderComponent>(textureToUse);
            spriteComp->getDimensions(width, height);
            renderComp = std::move(spriteComp);
        } else {
            // No texture: use the fallback values.
            width = fallbackWidth;
            height = fallbackHeight;
            renderComp = std::make_unique<ShapeRenderComponent>(width, height, fallbackColor);
        }

        entity->setSize(width, height);
        entity->setRenderComponent(std::move(renderComp));
    }

    return entity;
}