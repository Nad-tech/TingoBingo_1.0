#pragma once

#include "Sprite.h"
#include "Emotion.h"
#include "BodyDimensions.h"

class Eyebrows : public Sprite
{
    public:
        Eyebrows(BodyDimensions& dimensions);
        
        void Initialise() override;

        void Update(float dt, bool speaking, Emotion emotion);
        void SetTransform(MyTransform transform);

    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;

        float foreheadOffset = 65; 

        float happyAnimationTimer = 0.0f;
        float nextHappyAnimation = 3.0f;

        float idleAnimationTimer = 0.0f;
        float nextIdleAnimation = 3.0f;
        
        bool wasHappy = false;
};