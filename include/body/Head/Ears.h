#pragma once

#include "Sprite.h"

class Ears : public Sprite
{
     public:
        void Initialise() override;
        void Update(float dt) override;
        void SetBodyHeadDimensions(
            float bwidth, 
            float bHeigh, 
            float hWidth, 
            float hHeight
        );

    private:
        //Ears-centre translation in local head coordinates.
        Vector2 localPositionOffset = {0, 0};

        float bodyWidth = 0.0f;
        float bodyHeight = 0.0f;
        float headWidth = 0.0f;
        float headHeight = 0.0f;
        
        float idleAnimationTimer = 0.0f;
        float nextIdleAnimation = 0.0;
};
