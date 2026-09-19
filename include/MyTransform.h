#pragma once

#include "raylib.h"

struct MyTransform
{
    Vector2 position = {0,0};
    Vector2 pivot = {0,0};
    float rotation = 0.0f;
    float scale = 1.0f;
};