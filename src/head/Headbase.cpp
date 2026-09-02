//====================================================
// HeadBase.cpp
//
// Handles the robot's main head sprite.
//
// The HeadBase is responsible for displaying the
// current head orientation and managing rotation
// between head frames.
//====================================================

#include "head/Headbase.h"
#include "Constants.h"

// Load the head sprite and initialise its animation.
void Headbase::Initialise()
{
    texture = LoadTexture("assets/images/TingoBingo/head/HeadBase.png");

    // Sprite sheet layout.
    const int COLUMNS = 1;
    const int ROWS = 1;

    // Calculate the size of a single animation frame.
    const int FRAME_WIDTH = texture.width / COLUMNS;
    const int FRAME_HEIGHT = texture.height / ROWS;

    const int TOTAL_FRAMES = COLUMNS * ROWS;

    // Animation settings.
    const float ROTATION = 0.0f;
    const float FRAME_DURATION = 0.02f;

    // Initialise the animation using the sprite sheet information.
    animation.Initialise
    (
        FRAME_WIDTH,
        FRAME_HEIGHT,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    rotation = ROTATION;
    scale = SCALE;

    origin = {50,235};
}

// Return the current head animation frame.
int Headbase::GetFrame() const
{
    return animation.GetFrame();
}

// Apply a rotation transform to the head sprite.
void Headbase::SetRotation(float rotation)
{
    Sprite::SetRotation(rotation);
}