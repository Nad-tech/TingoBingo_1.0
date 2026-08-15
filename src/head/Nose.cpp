//====================================================
// Nose.cpp
//
// Handles the robot's nose sprite and animation.
// The nose can play a short wiggle animation to add
// subtle life to the robot's idle behaviour.
//====================================================

#include "head/Nose.h"
#include "Constants.h"

// Load the nose sprite sheet and initialise its animation.
void Nose::Initialise()
{
    texture = LoadTexture("assets/images/TingoBingo/head/nose.png");

    // Sprite sheet layout.
    const int COLUMNS = 4;
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

// Advance the nose animation.
void Nose::Update(float dt)
{
    Sprite::Update(dt);

    //Idle behaviour
    //Wiggle nose at random intervals
    idleAnimationTimer += dt;

    if(idleAnimationTimer > nextIdleAnimation)
    {
        idleAnimationTimer = 0.0f;
        nextIdleAnimation = GetRandomValue(1000, 5000) / 1000.0f;
        animation.Play(0, 3, AnimationPriority::Idle);
    }
}

    