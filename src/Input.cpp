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
#include "Constants.h"

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

// Return the current mouse position, clamped to the screen dimensions.
Vector2 Input::MousePosition() const
{
    Vector2 mouse = GetMousePosition();
    Vector2 clampedMouse = mouse;

    if(mouse.x >= 0 && mouse.x < SCREEN_WIDTH)
    {
        clampedMouse.x = mouse.x;
    }

    if(mouse.y >= 0 && mouse.y < SCREEN_HEIGHT)
    {
        clampedMouse.y = mouse.y;
    }

    return clampedMouse;
}

bool Input::SpacePressed() const
{
    return IsKeyDown(KEY_SPACE);
}

bool Input::H_Pressed() const
{
    return IsKeyDown(KEY_H);
}

bool Input::LeftMouseButtonPressed() const
{
    return IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}