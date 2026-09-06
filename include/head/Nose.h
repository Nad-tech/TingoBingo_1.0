#pragma once

#include "Sprite.h"
#include "raylib.h"

class Nose : public Sprite
{
    public:
        void Initialise() override;
        void Update(float dt) override;
        void Draw() const override;
        void SetBodyHeadDimensions(
            float bwidth, 
            float bHeigh, 
            float hWidth, 
            float hHeight
        );

    private:
        float bodyWidth = 0.0f;
        float bodyHeight = 0.0f;
        float headWidth = 0.0f;
        float headHeight = 0.0f;
        
        //Idle
        float localRotation = 0.0f;
        float idleTimer = 0.0f;
        bool noseRotating = false;
        float nextNoseRotation = 0;
        float noseRotateTimer = 0;
        
        //Wiggle
        Vector2 homeAnchorPoint = {0,0};
        float wiggleTimer = 0.0f;
        bool noseWiggling = false;
        float nextNoseWiggle = 0;
        float noseWiggleTimer = 0;
        float wiggleOffSetX = 0;
        float wiggleOffsetY = 0;

        const float NEXT_ROTATION_TIME = 5.0f;
        const float LOCAL_ROTATION_SPEED = 700.0f;

        const float NEXT_WIGGLE_TIME = 3.0f;
        const float WIGGLE_SPEED = 25.0f;
        const float WIGGLE_AMOUNT = 5.0f;
}; 
