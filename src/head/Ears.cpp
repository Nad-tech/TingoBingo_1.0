//====================================================
// Ears.cpp
//
// Handles the robot's ear sprites and animation.
// The ears can play a short wiggle animation when
// triggered.
//====================================================

#include "Body/Head/Ears.h"
#include "Constants.h"

Ears::Ears(BodyDimensions& dimensions) : dimensions(dimensions)
{}

void Ears::Initialise()
{
    // Load the ear sprite sheet.
    texture = LoadTexture("assets/images/TingoBingo/head/ears.png");

    // Sprite sheet layout.
    const int COLUMNS = 5;
    const int ROWS = 1;

    // Calculate the size of a single animation frame.
    dimensions.earsWidth = texture.width / COLUMNS;
    dimensions.earsHeight = texture.height / ROWS;

    const int TOTAL_FRAMES = COLUMNS * ROWS;

    // Animation settings.
    const float ROTATION = 0.0f;
    const float FRAME_DURATION = 0.09f;

    // Initialise the animation using the sprite sheet information.
    animation.Initialise
    (
        dimensions.earsWidth,
        dimensions.earsHeight,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    positionOffset = {0, 0};
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

void Ears::SetTransform(MyTransform parentTransform)
{
    transform = MakeChildTransform(parentTransform, positionOffset);
}
