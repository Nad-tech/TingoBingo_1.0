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

Eyes::Eyes(BodyDimensions& dimensions) : 
    dimensions(dimensions),
    pupils(dimensions)
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

    const int TOTAL_FRAMES = COLUMNS * ROWS;
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

    dimensions.eyesYoffset = 30.0f;

    positionOffset = {
        0, dimensions.eyesYoffset
    };

    pupils.Initialise();
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

    pupils.Update(dt);
}

void Eyes::Draw() const
{
    Sprite::Draw();
    pupils.Draw();
}

void Eyes::SetTransform(MyTransform parentTransform)
{
    transform = parentTransform;
    transform.position.y += positionOffset.y;
    Sprite::SetTransform(transform);
    pupils.SetTransform(transform);
}

Pupils& Eyes::GetPupils()
{
    return pupils;
}

void Eyes::LookAt(Vector2 point)
{
    pupils.LookAt(point);
}

void Eyes::LookForward()
{
    pupils.LookForward();
}

void Eyes::ShutDown()
{
    pupils.Shutdown();
    Sprite::Shutdown();
}