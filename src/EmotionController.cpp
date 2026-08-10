#include "EmotionController.h"
#include "head\Head.h"

EmotionController::EmotionController(Head& h)
    : head(h),
      eyebrowsHappyAnimationTimer(0.0f),
      nextEyebrowsHappyAnimation(0.0f),
      currentEmotion(Emotion::Neutral)
{}

void EmotionController::Update(float dt)
{
    UpdateEyebrows(dt);
}

void EmotionController::SetEmotion(Emotion emotion)
{
    currentEmotion = emotion;
}

void EmotionController::UpdateEyebrows(float dt)
{
    if(currentEmotion == Emotion::Neutral)
    {
        //head.PlayIdleEyebrowsAnimation();
    }
    
    if(currentEmotion == Emotion::Happy) {
        eyebrowsHappyAnimationTimer += dt;

       if (eyebrowsHappyAnimationTimer > nextEyebrowsHappyAnimation)
       {
            head.PlayHappyEyebrowsAnimation();

            eyebrowsHappyAnimationTimer = 0.0f;
            nextEyebrowsHappyAnimation = GetRandomValue(1000, 1000) / 1000.0f;
        }
    }
}