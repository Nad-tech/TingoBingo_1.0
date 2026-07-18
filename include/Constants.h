//==================================================
//
// Template Project
//
// Version 1.0
//
// Raylib
// C++20
//
//==================================================

#pragma once

#include "raylib.h"

constexpr int SCREEN_WIDTH = 700;
constexpr int SCREEN_HEIGHT = 600;
constexpr char WINDOW_TITLE[] = "TingoBingo";
constexpr int TARGET_FPS = 60;

constexpr float SPRITESHEET_FRAME_SIZE = 512;
constexpr Vector2 ROBOT_INITIAL_POSITION = {
    SCREEN_WIDTH / 2.0f - SPRITESHEET_FRAME_SIZE/2,
    SCREEN_HEIGHT / 2.0f - SPRITESHEET_FRAME_SIZE/2
};