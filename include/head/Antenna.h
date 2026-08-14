#pragma once

#include "Sprite.h"

class Antenna : public Sprite 
{
    public:
        void Initialise() override;
        void Update(float dt) override;
        void PlayWiggle();
    
    private:
        float antennaAnimationTimer = 0.0f;
        float nextAntennaAnimation = 3.0f;
};
