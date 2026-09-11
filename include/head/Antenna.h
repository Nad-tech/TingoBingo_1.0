#pragma once

#include "Sprite.h"

class Antenna : public Sprite 
{
    public:
        void Initialise() override;
        void Update(float dt) override;
        void SetBodyHeadDimensions(float bW, float bH, float hW, float hH);
    
    private:
        float antennaAnimationTimer = 0.0f;
        float nextAntennaAnimation = 3.0f;

        Vector2 localPositionOffset = {};
        float topOfHeadOffset = 46.0f;
        float bodyWidth = 0;
        float bodyHeight = 0;
        float headWidth = 0;
        float headHeight = 0;
};
