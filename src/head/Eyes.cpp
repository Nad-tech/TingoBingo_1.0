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

Eyes::Eyes(BodyDimensions& dimensions) : dimensions(dimensions)
{
}

void Eyes::Initialise()
{
    // Load the eye sprite sheet.
    texture = LoadTexture("assets/images/TingoBingo/head/eyes.png");

    // Sprite sheet layout.
    const int COLUMNS = 5;
    const int ROWS = 1;

    // Calculate the size of a single animation frame.
    dimensions.eyesWidth = texture.width / COLUMNS;
    dimensions.eyesHeight = texture.height / ROWS;

    dimensions.eyesYoffset = 30.0f;

    const int TOTAL_FRAMES = COLUMNS * ROWS;

    // Animation settings.
    const float ROTATION = 0.0f;
    const float FRAME_DURATION = 0.06f;

    // Initialise the animation using the sprite sheet information.
    animation.Initialise
    (
        dimensions.eyesWidth,
        dimensions.eyesHeight,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    rotation = ROTATION;
    scale = SCALE;

    anchorOffset = {
        dimensions.eyesWidth / 2.0f,
        dimensions.eyesHeight / 2.0f + 
        dimensions.bodyHeight / 2.0f + 
        dimensions.headHeight / 2.0f + 
        dimensions.neckHeight +
        dimensions.eyesYoffset
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
