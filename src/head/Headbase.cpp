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
}

// Return the current head animation frame.
int Headbase::GetFrame() const
{
    return animation.GetFrame();
}

// Rotate the head one frame to the left.
void Headbase::RotateLeft()
{
    animation.PreviousFrame();
}

// Rotate the head one frame to the right.
void Headbase::RotateRight()
{
    animation.NextFrame();
}

// Gradually return the head to its forward-facing position
// using the shortest rotation direction.
void Headbase::ReturnToCentre()
{
    int frame = animation.GetFrame();
    int halfTurn = animation.GetTotalFrames() / 2;

    if (frame == 0)
        return;

    // Decide which direction requires the fewest frames.
    if (frame < halfTurn)
    {
        animation.PreviousFrame();
    }
    else
    {
        animation.NextFrame();
    }
}

// Apply a rotation transform to the head sprite.
void Headbase::SetRotation(float rotation)
{
    Sprite::SetRotation(rotation);
}