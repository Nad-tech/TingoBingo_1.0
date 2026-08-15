//====================================================
// Eyebrows.cpp
//
// Handles the robot's eyebrow sprites and animation.
// The eyebrows can play idle and emotional animations.
//====================================================

#include "head/Eyebrows.h"
#include "Constants.h"
#include "Emotion.h"
#include "Animation.h"

void Eyebrows::Initialise()
{
    // Load the eyebrow sprite sheet.
    texture = LoadTexture("assets/images/TingoBingo/head/eyebrows.png");

    // Define the sprite sheet layout.
    const int COLUMNS = 4;
    const int ROWS = 1;

    // Determine the dimensions of each frame.
    const int FRAME_WIDTH = texture.width / COLUMNS;
    const int FRAME_HEIGHT = texture.height / ROWS;

    const int TOTAL_FRAMES = COLUMNS * ROWS;

    // Configure the eyebrow animation timing and orientation.
    const float ROTATION = 0.0f;
    const float FRAME_DURATION = 0.3f;

    // Create the animation from the sprite sheet.
    animation.Initialise
    (
        FRAME_WIDTH,
        FRAME_HEIGHT,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    // Apply the default sprite transform.
    rotation = ROTATION;
    scale = SCALE;
}

void Eyebrows::UpdateEyebrows(float dt, bool speaking, Emotion emotion)
{
    // Update the base sprite behaviour before handling eyebrow animation.
    Sprite::Update(dt);

    // Speaking and happiness both use the expressive eyebrow animation.
    bool happy = speaking || emotion == Emotion::Happy;

    // Start the happy animation immediately when entering the happy state.
    if (happy && !wasHappy)
    {
        animation.Play(2, 3, AnimationPriority::Emotion);

        // Reset the timer and choose a random delay before the next wiggle.
        happyAnimationTimer = 0.0f;
        nextHappyAnimation = GetRandomValue(1000, 5000) / 1000.0f;

        wasHappy = true;
        return;
    }

    // While happy, occasionally repeat the eyebrow wiggle.
    if (happy)
    {
        happyAnimationTimer += dt;

        if (happyAnimationTimer > nextHappyAnimation)
        {
            animation.Play(2, 3, AnimationPriority::Emotion);

            // Reset the timer and choose a new random interval.
            happyAnimationTimer = 0.0f;
            nextHappyAnimation =
                GetRandomValue(1000, 5000) / 1000.0f;
        }

        return;
    }

    // Restore the idle animation when the happy state ends.
    if (wasHappy)
    {
        animation.Stop();
        animation.Play(0, 1, AnimationPriority::Idle);

        // Reset the idle timer so the next idle animation is delayed.
        idleAnimationTimer = 0.0f;
        nextIdleAnimation =
            GetRandomValue(1000, 5000) / 1000.0f;

        wasHappy = false;
        return;
    }

    // In the neutral state, occasionally play a small idle movement.
    idleAnimationTimer += dt;

    if (idleAnimationTimer > nextIdleAnimation)
    {
        animation.Stop();
        animation.Play(0, 1, AnimationPriority::Idle);

        // Reset the timer and randomise the next idle movement.
        idleAnimationTimer = 0.0f;
        nextIdleAnimation =
            GetRandomValue(1000, 5000) / 1000.0f;
    }
}