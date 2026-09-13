//====================================================
// Eyes.cpp
//
// Handles the robot's eye sprites and blink animation.
// The eyes are animated independently from the head,
// allowing facial expressions without changing the
// head rotation sprite.
//====================================================

#include "Body/Head/Eyes.h"
#include "Constants.h"

void Eyes::Initialise()
{
    // Load the eye sprite sheet.
    texture = LoadTexture("assets/images/TingoBingo/head/eyes.png");

    // Sprite sheet layout.
    const int COLUMNS = 5;
    const int ROWS = 1;

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

    anchorOffset = {
        FRAME_WIDTH / 2.0f,
        FRAME_HEIGHT / 2.0f + 
        bodyHeight / 2.0f + 
        headHeight / 2.0f + 
        neckHeight +
        eyesOffset.y
    };
}

void Eyes::Update(float dt)
{
    // Advance the eye animation.
    Sprite::Update(dt);

    //Idle beahviour
    //Blink at random intervals
    idleAnimationTimer += dt;
    
    if(idleAnimationTimer > nextIdleAnimation)
    {
        animation.Play(0, 4, AnimationPriority::Idle);
        idleAnimationTimer = 0.0f;
        nextIdleAnimation = GetRandomValue(1000, 5000) / 1000.0f;
    }
}

void Eyes::SetBodyHeadNeckDimensions(
            float bW, float bH,
            float hW, float hH,
            float nW, float nH
        )
{
    bodyWidth = bW;
    bodyHeight = bH;
    headWidth = hW;
    headHeight = hH;
    neckWidth = nW;
    neckHeight = nH;
}

float Eyes::GetYOffset()
{
    return eyesOffset.y;
}