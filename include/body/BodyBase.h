#pragma once

#include "Sprite.h"
#include "BodyDimensions.h"
class BodyBase : public Sprite 
{
    public:
        BodyBase(BodyDimensions& dimensions);
        void Initialise() override;
        
    private:
        BodyDimensions& dimensions;
};
