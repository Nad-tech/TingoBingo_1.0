#pragma once

#include "SpritePart.h"

class Eyes : public SpritePart
{
    public:
        void Initialise() override;
        void Update(float dt) override;
        void Draw() const override;

    private:
        float blinkTimer = 0;
        bool blinking = false;
}; 
