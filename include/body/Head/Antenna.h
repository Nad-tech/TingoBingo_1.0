#pragma once

#include "Sprite.h"
#include "BodyDimensions.h"

class Antenna : public Sprite 
{
    public:
        Antenna(BodyDimensions& dimensions);
        void Initialise() override;
        void Update(float dt) override;

    private:
        BodyDimensions& dimensions;
        float antennaAnimationTimer = 0.0f;
        float nextAntennaAnimation = 3.0f;

        Vector2 localPositionOffset = {};
        float topOfHeadOffset = 46.0f;
};
