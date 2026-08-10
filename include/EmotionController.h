#pragma once

#include "head\Head.h"

enum class Emotion
{
    Neutral,
    Happy,
    Sad,
    Angry,
    Surprised
};

class EmotionController
{
    public:
        EmotionController(Head& head);

        void Update(float dt);
        void UpdateEyebrows(float dt);
        void SetEmotion(Emotion emotion);

    private:
        Head& head;
        
        float eyebrowsHappyAnimationTimer;
        float nextEyebrowsHappyAnimation;

        Emotion currentEmotion;
};