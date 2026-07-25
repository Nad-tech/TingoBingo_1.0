#pragma once

#include "Sprite.h"

class Eyes : public Sprite
{
    public:
        void Initialise() override;
        void Update(float dt) override;
    
        void PlayBlink();

    private:
}; 
