#pragma once

#include "Sprite.h"
#include <string>

class Pupil : public Sprite
{
    public:
        void Initialise() override;
        void Update(float dt) override;
        void SetBodyHeadNeckEyeOffsetDimensions(
            float bW, float bH, 
            float hW, float hH,
            float nW, float nH,
            float eyesYOffset
        );
        void SetSide(std::string side);

    private:
        float bodyWidth;
        float bodyHeight;
        float headWidth;
        float headHeight;
        float neckWidth;
        float neckHeight;
        float eyesYOffset;
        std::string side; // "left" or "right"
        float sideOffset = 40;
};