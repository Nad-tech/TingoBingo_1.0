#pragma once

#include "Sprite.h"

class Nose : public Sprite
{
    public:
        void Initialise() override;
        void Update(float dt) override;

        void PlayWiggle();

    private:
}; 
