#pragma once

#include "Sprite.h"

class Eyes : public Sprite
{
    public:
        void Initialise() override;
        void Update(float dt) override;
        void SetBodyHeadNeckDimensions(
            float bW, float bH,
            float hW, float hH,
            float nW, float nH
        );
        float GetYOffset();

    private:
        float idleAnimationTimer = 0.0f;
        float nextIdleAnimation = 0.0f;
        float headWidth;
        float headHeight;
        float bodyWidth;
        float bodyHeight;
        float neckWidth;
        float neckHeight;
        Vector2 eyesOffset = {0, 30.0f};
}; 
