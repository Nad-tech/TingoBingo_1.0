//====================================================
// Mouth.cpp
//
// Handles the robot's mouth sprite and idle animation.
// The mouth can play a simple animation to give the
// robot a more lifelike appearance.
//====================================================

#include "Body/Head/Mouth.h"
#include "Constants.h"
#include "Emotion.h"

Mouth::Mouth(BodyDimensions& dimensions) : dimensions(dimensions)
{}

// Load the mouth sprite sheet and initialise its animation.
void Mouth::Initialise()
{
    texture = LoadTexture("assets/images/TingoBingo/head/mouth.png");

    // Sprite sheet layout.
    const int COLUMNS = 3;
    const int ROWS = 1;

    // Calculate the size of a single animation frame.
    dimensions.mouthWidth = texture.width / COLUMNS;
    dimensions.mouthHeight = texture.height / ROWS;

    const int TOTAL_FRAMES = COLUMNS * ROWS;

    // Initialise the animation using the sprite sheet information.
    animation.Initialise
    (
        dimensions.mouthWidth,
        dimensions.mouthHeight,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    positionOffset = {
        0,
        0
    };
}

// Advance the mouth animation.
void Mouth::UpdateMouth(float dt, bool speaking, Emotion emotion)
{
    Sprite::Update(dt);
    
    if (emotion == Emotion::Happy && !speaking)
    {
        frame = 0;
        frameTimer = 0.0f;
        animation.SetFrame(frame);
        return;
    }

    if (!speaking)
    {
        frame = 1;
        frameTimer = 0.0f;
        animation.SetFrame(frame);
        return;
    }

    //Animate mouth while speaking
    frameTimer += dt;

    if (frameTimer >= FRAME_DURATION)
    {
        frameTimer -= FRAME_DURATION;
        frame = (frame == 1) ? 2 : 1;
        animation.SetFrame(frame);
    }
}

void Mouth::SetTransform(MyTransform parentTransform)
{
    transform = MakeChildTransform(parentTransform, positionOffset);
}
