#pragma once

#include "Sprite.h"
#include "Emotion.h"
#include "BodyDimensions.h"

class Eyebrows : public Sprite
{
    public:
        Eyebrows(BodyDimensions& dimensions);
        void Initialise() override;
        void UpdateEyebrows(float dt, bool speaking, Emotion emotion);
       
    private:
        BodyDimensions& dimensions;

        float foreheadOffset = 65; 

        float happyAnimationTimer = 0.0f;
        float nextHappyAnimation = 3.0f;

        float idleAnimationTimer = 0.0f;
        float nextIdleAnimation = 3.0f;
        
        bool wasHappy = false;
};