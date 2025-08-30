//
// Created by capn on 8/29/25.
//
#pragma once

namespace GameConfig {
    // Window and Rendering
    const int FIXED_LOGICAL_HEIGHT = 1080;
    const int TILE_SIZE = 32;


    // Physics
    const float GRAVITY = 0.5f;

    // Player Specific
    const float PLAYER_SPEED = 5.0f;
    const float JUMP_FORCE = 15.0f;
    const int PLAYER_WIDTH = 32;
    const int PLAYER_HEIGHT = 48;


    //Enemy Specifc
    const float ENEMY_SPEED = 2.0f; // <-- ADD THIS
    const int ENEMY_WIDTH = 32;    // <-- ADD THIS
    const int ENEMY_HEIGHT = 32;   // <-- ADD THIS

}