//====================================================
// Mouth.cpp
//
// Handles the robot's mouth sprite and idle animation.
// The mouth can play a simple animation to give the
// robot a more lifelike appearance.
//====================================================

#include "head/Mouth.h"
#include "Constants.h"

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
void Mouth::UpdateMouth(float dt, bool speaking)
{
    Sprite::Update(dt);

    if(!speaking)
    {
        frame = 0;
        frameTimer = 0.0f;
        animation.SetFrame(0);
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
void Mouth::PlayIdleMouth()
{
    if (!animation.IsPlaying())
    {
        animation.Play(0, 1);
    }
}