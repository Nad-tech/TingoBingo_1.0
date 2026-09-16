#pragma once

#include "Sprite.h"
#include "BodyDimensions.h"

class Eyes : public Sprite
{
    public:
        Eyes(BodyDimensions& dimensions);
        void Initialise() override;
        void Update(float dt) override;

    private:
        BodyDimensions& dimensions;

        // TODO: make pupils child of Eyes
        float idleAnimationTimer = 0.0f;
        float nextIdleAnimation = 0.0f;
}; 
