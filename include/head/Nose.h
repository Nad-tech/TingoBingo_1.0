#pragma once

#include "Sprite.h"

class Nose : public Sprite
{
    public:
        void Initialise() override;
        void Update(float dt) override;
    
    private:
        float blinkTimer = 0.0f;
        float nextBlink = 3.0f;
}; 
