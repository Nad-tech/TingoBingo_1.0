//====================================================
// Antenna.cpp
//
// Handles the robot's antenna sprite and animation.
// The antenna can play a short wiggle animation when
// triggered.
//====================================================

#include "head/Antenna.h"
#include "Constants.h"

void Antenna::Initialise()
{
    // Load the antenna sprite sheet.
    texture = LoadTexture("assets/images/TingoBingo/head/antenna.png");

    // Sprite sheet layout.
    const int COLUMNS = 4;
    const int ROWS = 2;

    // Calculate the size of a single animation frame.
    const int FRAME_WIDTH = texture.width / COLUMNS;
    const int FRAME_HEIGHT = texture.height / ROWS;

    const int TOTAL_FRAMES = COLUMNS * ROWS;

    // Animation settings.
    const float ROTATION = 0.0f;
    const float FRAME_DURATION = 0.06f;

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

void Antenna::Update(float dt)
{
    // Advance the antenna animation.
    Sprite::Update(dt);
}

void Antenna::PlayWiggle()
{
    // Start the wiggle animation if it isn't already playing.
    if (!animation.IsPlaying())
    {
        animation.Play(0, 7);
    }
}