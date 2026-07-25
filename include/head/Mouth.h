#pragma once

#include "Sprite.h"

class Mouth : public Sprite
{
    public:
        void Initialise() override;
        void Update(float dt) override;
    
        void PlayIdleMouth();

    private:
};