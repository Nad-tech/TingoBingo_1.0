#pragma once

#include "Sprite.h"
#include "Emotion.h"

class Mouth : public Sprite
{
    public:
        void Initialise() override;
        void UpdateMouth(float dt, bool speaking, Emotion emotion);
        void SetBodyHeadNeckDimensions(
            float bW, float bH, 
            float hW, float hH, 
            float nW, float nH 
        );

  
    private:
        int frame = 0;
        float frameTimer = 0.0f;
        const float FRAME_DURATION = 0.3f;

        Vector2 localPositionOffset = {};
        float mouthDisplayOffset = 28.0f;

        float bodyWidth = 0;
        float bodyHeight = 0;
        float headWidth = 0;
        float headHeight = 0;
        float neckWidth;
        float neckHeight;
};