#include "IdleController.h"

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

void IdleController::Update(float dt)
{
    UpdateAntenna(dt);
    UpdateEars(dt);
    UpdateEyebrows(dt);
    UpdateEyes(dt);
    UpdateMouth(dt);
    UpdateNose(dt);
}

void IdleController::UpdateAntenna(float dt)
{
    antennaIdleAnimationTimer += dt;
    if(antennaIdleAnimationTimer > nextAntennaIdleAnimation)
    {
        head.PlayIdleAntennaAnimation();
        antennaIdleAnimationTimer = 0.0f;
        nextAntennaIdleAnimation = GetRandomValue(1000,5000) / 1000.0f;
    }
}

void IdleController::UpdateEars(float dt)
{
    earsIdleAnimationTimer += dt;
    if(earsIdleAnimationTimer > nextEarsIdleAnimation)
    {
        head.PlayIdleEarsAnimation();
        earsIdleAnimationTimer = 0.0f;
        nextEarsIdleAnimation = GetRandomValue(1000,5000) / 1000.0f;
    }
}

void IdleController::UpdateEyebrows(float dt)
{
    eyebrowsIdleAnimationTimer += dt;
    if(eyebrowsIdleAnimationTimer > nextEyebrowsIdleAnimation)
    {
        head.PlayIdleEyebrowsAnimation();
        eyebrowsIdleAnimationTimer = 0.0f;
        nextEyebrowsIdleAnimation = GetRandomValue(1000,5000) / 1000.0f;
    }
}

void IdleController::UpdateEyes(float dt)
{
    eyesIdleAnimationTimer += dt;
    if(eyesIdleAnimationTimer > nextEyesIdleAnimation)
    {
        head.PlayIdleEyesAnimation();
        eyesIdleAnimationTimer = 0.0f;
        nextEyesIdleAnimation = GetRandomValue(1000,5000) / 1000.0f;
    }
}

void IdleController::UpdateMouth(float dt)
{
    mouthIdleAnimationTimer += dt;
    if(mouthIdleAnimationTimer > nextMouthIdleAnimation)
    {
        head.PlayIdleMouthAnimation();
        mouthIdleAnimationTimer = 0.0f;
        nextMouthIdleAnimation = GetRandomValue(1000,5000) / 1000.0f;
    }
}

void IdleController::UpdateNose(float dt)
{
    noseIdleAnimationTimer += dt;
    if(noseIdleAnimationTimer > nextNoseIdleAnimation)
    {
        head.PlayIdleNoseAnimation();
        noseIdleAnimationTimer = 0.0f;
        nextNoseIdleAnimation = GetRandomValue(1000,5000) / 1000.0f;
    }
}

