#pragma once

#include "raylib.h"
class Input
{
public:
    bool LeftPressed() const;
    bool RightPressed() const;
    bool SpacePressed() const;
    Vector2 MousePosition() const;
    bool H_Pressed() const;
    bool LeftMouseButtonPressed() const;
};