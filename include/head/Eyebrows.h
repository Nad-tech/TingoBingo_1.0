#pragma once

#include "Sprite.h"
#include "Emotion.h"

class Eyebrows : public Sprite
{
    public:
        void Initialise() override;
        void UpdateEyebrows(float dt, bool speaking, Emotion emotion);

    private:
        float happyAnimationTimer = 0.0f;
        float nextHappyAnimation = 3.0f;

        float idleAnimationTimer = 0.0f;
        float nextIdleAnimation = 3.0f;
        
        bool wasHappy = false;
};