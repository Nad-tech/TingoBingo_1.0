#include "Input.h"
#include "raylib.h"

bool Input::LeftPressed() const
{
    return IsKeyDown(KEY_LEFT);
}

bool Input::RightPressed() const
{
    return IsKeyDown(KEY_RIGHT);
}