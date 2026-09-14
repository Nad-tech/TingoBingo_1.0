//====================================================
// Ears.cpp
//
// Handles the robot's ear sprites and animation.
// The ears can play a short wiggle animation when
// triggered.
//====================================================

#include "Body/Head/Ears.h"
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

    localPositionOffset =
    {
        FRAME_WIDTH / 2.0f,
        FRAME_HEIGHT / 2.0f
        + bodyHeight / 2.0f
        + headHeight / 2.0f
        + neckHeight
    };

    anchorOffset = localPositionOffset;
}

void Ears::Update(float dt)
{
    // Advance the ear animation.
    Sprite::Update(dt);

    //Idle behavior
    //Wiggle ears at random intervals
    idleAnimationTimer += dt;

    if(idleAnimationTimer > nextIdleAnimation)
    { 
        animation.Play(0, 4, AnimationPriority::Idle);
        idleAnimationTimer = 0.0f;
        nextIdleAnimation = GetRandomValue(1000, 5000) / 1000.0f;
    }
}

void Ears::SetBodyHeadNeckDimensions(
    float bW, float bH, 
    float hW, float hH, 
    float nW, float nH 
)
{
    // Store the supplied body dimensions.
    bodyWidth = bW;
    bodyHeight = bH;

    // Store the supplied head dimensions.
    headWidth = hW;
    headHeight = hH;

    neckWidth = nW;
    neckHeight = nH;
}