#pragma once

#include "Sprite.h"

class Eyebrows : public Sprite
{
    public:
        void Initialise() override;
        void UpdateEyebrows(float dt);
    
        void PlayIdleWiggle();
        void PlayHappyWiggle();

    private:
};