#pragma once

#include "Sprite.h"
#include "BodyDimensions.h"

class Ears : public Sprite
{
     public:
        Ears(BodyDimensions& dimensions);
        void Initialise() override;
        void Update(float dt) override;

    private:
        BodyDimensions& dimensions;

        float idleAnimationTimer = 0.0f;
        float nextIdleAnimation = 0.0;
};
