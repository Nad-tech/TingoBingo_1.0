//====================================================
// Input.cpp
//
// Provides a simple interface for reading player input.
//
// Wrapping Raylib input functions keeps the rest of the
// project independent of the underlying input library.
//====================================================

#include "Input.h"
#include "raylib.h"

// Returns true while the left arrow key is held down.
bool Input::LeftPressed() const
{
    return IsKeyDown(KEY_LEFT);
}

// Returns true while the right arrow key is held down.
bool Input::RightPressed() const
{
    return IsKeyDown(KEY_RIGHT);
}

// Return the current mouse position.
Vector2 Input::MousePosition() const
{
    return GetMousePosition();
}

bool Input::SpacePressed() const
{
    return IsKeyDown(KEY_SPACE);
}