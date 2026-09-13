#pragma once

#include "Sprite.h"

class Eyes : public Sprite
{
    public:
        void Initialise() override;
        void Update(float dt) override;
        void SetHeadDimensions(float width, float height);
        void SetBodyDimensions(float width, float height);
        float GetYOffset();

    private:
        float idleAnimationTimer = 0.0f;
        float nextIdleAnimation = 0.0f;
        float headWidth;
        float headHeight;
        float bodyWidth;
        float bodyHeight;
        Vector2 eyesOffset = {0, 30.0f};
}; 
