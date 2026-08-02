//====================================================
// Ears.cpp
//
// Handles the robot's ear sprites and animation.
// The ears can play a short wiggle animation when
// triggered.
//====================================================

#include "head/Ears.h"
#include "Constants.h"

void Ears::Initialise()
{
    // Load the ear sprite sheet.
    texture = LoadTexture("assets/images/TingoBingo/head/ears.png");

    // Sprite sheet layout.
    const int COLUMNS = 5;
    const int ROWS = 1;

    // Calculate the size of a single animation frame.
    const int FRAME_WIDTH = texture.width / COLUMNS;
    const int FRAME_HEIGHT = texture.height / ROWS;

    const int TOTAL_FRAMES = COLUMNS * ROWS;

    // Animation settings.
    const float ROTATION = 0.0f;
    const float FRAME_DURATION = 0.09f;

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

void Ears::Update(float dt)
{
    // Advance the ear animation.
    Sprite::Update(dt);
}

void Ears::PlayWiggle()
{
    // Start the wiggle animation if it isn't already playing.
    if (!animation.IsPlaying())
    {
        animation.Play(0, 4);
    }
}