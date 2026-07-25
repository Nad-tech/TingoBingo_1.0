#pragma once

#include "raylib.h"
class Input
{
public:
    bool LeftPressed() const;
    bool RightPressed() const;
    Vector2 MousePosition() const;
};