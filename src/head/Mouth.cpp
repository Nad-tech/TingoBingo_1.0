//====================================================
// Mouth.cpp
//
// Handles the robot's mouth sprite and idle animation.
// The mouth can play a simple animation to give the
// robot a more lifelike appearance.
//====================================================

#include "head/Mouth.h"
#include "Constants.h"
#include "Emotion.h"

// Load the mouth sprite sheet and initialise its animation.
void Mouth::Initialise()
{
    texture = LoadTexture("assets/images/TingoBingo/head/mouth.png");

    // Sprite sheet layout.
    const int COLUMNS = 3;
    const int ROWS = 1;

    // Calculate the size of a single animation frame.
    const int FRAME_WIDTH = texture.width / COLUMNS;
    const int FRAME_HEIGHT = texture.height / ROWS;

    const int TOTAL_FRAMES = COLUMNS * ROWS;

    // Animation settings.
    const float ROTATION = 0.0f;
    
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

// Advance the mouth animation.
void Mouth::UpdateMouth(float dt, bool speaking, Emotion emotion)
{
    Sprite::Update(dt);

    if (emotion == Emotion::Happy && !speaking)
    {
        frame = 0;
        frameTimer = 0.0f;
        SetHappy();
        return;
    }

    if (!speaking)
    {
        frame = 1;
        frameTimer = 0.0f;
        SetIdle();
        return;
    }

    frameTimer += dt;

    if (frameTimer >= FRAME_DURATION)
    {
        frameTimer -= FRAME_DURATION;
        frame = (frame == 1) ? 2 : 1;
        animation.SetFrame(frame);
    }
}

// Start the idle mouth animation if it isn't already playing.
void Mouth::SetIdle()
{
    animation.SetFrame(1);
}

void Mouth::SetHappy()
{
    animation.SetFrame(0);
}