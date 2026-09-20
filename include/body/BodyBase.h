#pragma once

#include "Sprite.h"
#include "BodyDimensions.h"
class BodyBase : public Sprite 
{
    public:
        BodyBase(BodyDimensions& dimensions);
        void Initialise() override;
        int GetFrame() const;
        
    private:
        BodyDimensions& dimensions;
};
