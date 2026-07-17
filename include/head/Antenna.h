#pragma once

#include "SpritePart.h"

class Antenna : public SpritePart 
{
    public:
        void Initialise() override;
        void Update(float dt) override;
        void Draw() const override;
};
