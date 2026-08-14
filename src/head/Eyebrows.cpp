//====================================================
// Eyebrows.cpp
//
// Handles the robot's eyebrow sprites and animation.
// The eyebrows can play a simple two-frame wiggle
// animation when triggered.
//====================================================

#include "head/Eyebrows.h"
#include "Constants.h"
#include "Emotion.h"

void Eyebrows::Initialise()
{
    // Load the eyebrow sprite sheet.
    texture = LoadTexture("assets/images/TingoBingo/head/eyebrows.png");

    // Sprite sheet layout.
    const int COLUMNS = 4;
    const int ROWS = 1;

    // Calculate the size of a single animation frame.
    const int FRAME_WIDTH = texture.width / COLUMNS;
    const int FRAME_HEIGHT = texture.height / ROWS;

    const int TOTAL_FRAMES = COLUMNS * ROWS;

    // Animation settings.
    const float ROTATION = 0.0f;
    const float FRAME_DURATION = 0.3f;

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

void Eyebrows::UpdateEyebrows(float dt, bool speaking, Emotion emotion)
{
    Sprite::Update(dt);
    
    if(emotion == Emotion::Neutral)
    {
        SetIdle();
    }

    if(emotion == Emotion::Happy)
    {
        SetHappy();
    }

    if(speaking) 
    {
        SetHappy();
    }

}

void Eyebrows::SetIdle()
{
    animation.SetFrame(0);
}

void Eyebrows::SetHappy()
{
    animation.SetFrame(2);
}