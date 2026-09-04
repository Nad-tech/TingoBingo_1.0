#pragma once

#include "Sprite.h"
#include <string>

class Pupil : public Sprite
{
    public:
        void Initialise() override;
        void Update(float dt) override;
        void SetHeadDimensions(float width, float height);
        void SetBodyDimensions(float width, float height);
        void SetEyesYOffset(float yOffset);
        void SetSide(std::string side);

    private:
        float bodyWidth;
        float bodyHeight;
        float headWidth;
        float headHeight;
        float eyesYOffset;
        std::string side; // "left" or "right"
        float sideOffset = 40;
};