//
// Created by capn on 8/29/25.
//

#include "EntityFactory.h"
#include "Player.h"
#include "Enemy.h" // We will create this in the next step

std::unique_ptr<Entity> EntityFactory::create(EntityType type, int tileSize, float x, float y) {
    std::unique_ptr<Entity> entity = nullptr;

    switch (type) {
        case EntityType::Player:
            entity = std::make_unique<Player>();
            break;
        case EntityType::BasicEnemy:
            entity = std::make_unique<Enemy>();
            break;
            // Add more cases here for new entity types
        default:
            // Return a nullptr if the type is unknown
            return nullptr;
    }

    // Initialize the created entity with common properties
    if (entity) {
        entity->init(tileSize, x, y);
    }

    return entity;
}