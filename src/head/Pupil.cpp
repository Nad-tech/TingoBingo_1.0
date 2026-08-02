//====================================================
// Pupil.cpp
//
// Handles the robot's pupil sprite.
//
// The pupil is drawn separately from the eyes so it
// can move independently when the robot looks around.
//====================================================

#include "head/Pupil.h"
#include "Constants.h"

// Load the pupil sprite and initialise its animation.
void Pupil::Initialise()
{
    texture = LoadTexture("assets/images/TingoBingo/head/pupil.png");

    // Sprite sheet layout.
    const int COLUMNS = 1;
    const int ROWS = 1;

    // Calculate the size of a single animation frame.
    const int FRAME_WIDTH = texture.width / COLUMNS;
    const int FRAME_HEIGHT = texture.height / ROWS;

    const int TOTAL_FRAMES = COLUMNS * ROWS;

    // Animation settings.
    const float ROTATION = 0.0f;
    const float FRAME_DURATION = 0.08f;

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

// Advance the pupil animation.
void Pupil::Update(float dt)
{
    Sprite::Update(dt);
}