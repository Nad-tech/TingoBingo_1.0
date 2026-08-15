#pragma once

#include "Sprite.h"

class Nose : public Sprite
{
    public:
        void Initialise() override;
        void Update(float dt) override;

    private:
        float idleAnimationTimer = 0.0f;
        float nextIdleAnimation = 3.0f;
}; 
