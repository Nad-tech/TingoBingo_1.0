#pragma once

#include "Sprite.h"
#include "BodyDimensions.h"

class Headbase : public Sprite 
{
    public:
        Headbase(BodyDimensions& dimensions);
        void Initialise() override;
        
    private:
        BodyDimensions& dimensions;
};
