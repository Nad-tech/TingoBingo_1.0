//====================================================
// IdleController.cpp
//
// Controls the robot's idle behaviour.
//
// Each facial feature has its own independent timer,
// allowing idle animations such as blinking, ear
// wiggles and nose wiggles to occur at random
// intervals, making the robot appear more lifelike.
//====================================================

#include "IdleController.h"

// Initialise the idle timers for each head component.
IdleController::IdleController(Head& h)
    : head(h),
      antennaIdleAnimationTimer(0.0f),
      nextAntennaIdleAnimation(3.0f),
      earsIdleAnimationTimer(0.0f),
      nextEarsIdleAnimation(3.0f),
      eyebrowsIdleAnimationTimer(0.0f),
      nextEyebrowsIdleAnimation(3.0f),
      eyesIdleAnimationTimer(0.0f),
      nextEyesIdleAnimation(3.0f),
      mouthIdleAnimationTimer(0.0f),
      nextMouthIdleAnimation(3.0f),
      noseIdleAnimationTimer(0.0f),
      nextNoseIdleAnimation(3.0f)
{
}

// Update every idle animation controller.
void IdleController::Update(float dt)
{
    UpdateAntenna(dt);
    UpdateEars(dt);
    UpdateEyebrows(dt);
    UpdateEyes(dt);
    //UpdateMouth(dt); speech controller controls mouth
    UpdateNose(dt);
    UpdateHead(dt);
}

// Trigger the antenna idle animation at random intervals.
void IdleController::UpdateAntenna(float dt)
{
    antennaIdleAnimationTimer += dt;

    if (antennaIdleAnimationTimer > nextAntennaIdleAnimation)
    {
        head.PlayIdleAntennaAnimation();

        antennaIdleAnimationTimer = 0.0f;
        nextAntennaIdleAnimation = GetRandomValue(1000, 5000) / 1000.0f;
    }
}

// Trigger the ear idle animation at random intervals.
void IdleController::UpdateEars(float dt)
{
    earsIdleAnimationTimer += dt;

    if (earsIdleAnimationTimer > nextEarsIdleAnimation)
    {
        head.PlayIdleEarsAnimation();

        earsIdleAnimationTimer = 0.0f;
        nextEarsIdleAnimation = GetRandomValue(1000, 5000) / 1000.0f;
    }
}

// Trigger the eyebrow idle animation at random intervals.
void IdleController::UpdateEyebrows(float dt)
{
    eyebrowsIdleAnimationTimer += dt;

    if (eyebrowsIdleAnimationTimer > nextEyebrowsIdleAnimation)
    {
       // head.PlayIdleEyebrowsAnimation();

        eyebrowsIdleAnimationTimer = 0.0f;
        nextEyebrowsIdleAnimation = GetRandomValue(1000, 5000) / 1000.0f;
    }
}

// Trigger the eye blink animation at random intervals.
void IdleController::UpdateEyes(float dt)
{
    eyesIdleAnimationTimer += dt;

    if (eyesIdleAnimationTimer > nextEyesIdleAnimation)
    {
        head.PlayIdleEyesAnimation();

        eyesIdleAnimationTimer = 0.0f;
        nextEyesIdleAnimation = GetRandomValue(1000, 5000) / 1000.0f;
    }
}

// Trigger the mouth idle animation at random intervals.
void IdleController::UpdateMouth(float dt)
{
    mouthIdleAnimationTimer += dt;

    if (mouthIdleAnimationTimer > nextMouthIdleAnimation)
    {
        head.PlayIdleMouthAnimation();

        mouthIdleAnimationTimer = 0.0f;
        nextMouthIdleAnimation = GetRandomValue(1000, 5000) / 1000.0f;
    }
}

// Trigger the nose idle animation at random intervals.
void IdleController::UpdateNose(float dt)
{
    noseIdleAnimationTimer += dt;

    if (noseIdleAnimationTimer > nextNoseIdleAnimation)
    {
        head.PlayIdleNoseAnimation();

        noseIdleAnimationTimer = 0.0f;
        nextNoseIdleAnimation = GetRandomValue(1000, 5000) / 1000.0f;
    }
}

// Update the head's idle movement.
void IdleController::UpdateHead(float dt)
{
    head.PlayIdleHeadTransform(dt);
}