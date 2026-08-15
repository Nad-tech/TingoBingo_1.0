#pragma once

#include "Sprite.h"

class Ears : public Sprite
{
     public:
        void Initialise() override;
        void Update(float dt) override;
   
    private:
        float idleAnimationTimer = 0.0f;
        float nextIdleAnimation = 0.0;
};