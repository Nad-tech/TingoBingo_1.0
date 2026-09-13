#pragma once

#include "Sprite.h"
#include "Emotion.h"

class Eyebrows : public Sprite
{
    public:
        void Initialise() override;
        void UpdateEyebrows(float dt, bool speaking, Emotion emotion);
        void SetBodyHeadDimensions(
            float bwidth, 
            float bHeigh, 
            float hWidth, 
            float hHeight
        );

    private:
        // Eyebrows-centre translation in local head coordinates.
        Vector2 localPositionOffset = {0, 0};
        float foreheadOffset = 65;

        float bodyWidth = 0.0f;
        float bodyHeight = 0.0f;
        float headWidth = 0.0f;
        float headHeight = 0.0f;
        

        float happyAnimationTimer = 0.0f;
        float nextHappyAnimation = 3.0f;

        float idleAnimationTimer = 0.0f;
        float nextIdleAnimation = 3.0f;
        
        bool wasHappy = false;
};