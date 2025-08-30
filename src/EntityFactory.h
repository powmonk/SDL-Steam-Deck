//
// Created by capn on 8/29/25.
//
#pragma once
#include "Entity.h"
#include "EntityType.h"
#include <memory>
#include <SDL2/SDL.h>

class EntityFactory {
public:
    // The static method that will create our entities
    static std::unique_ptr<Entity> create(
        EntityType type,
        float x,
        float y,
        int tileSize,
        SDL_Texture* playerTexture,
        SDL_Texture* enemyTexture
    );
};