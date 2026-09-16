#pragma once

#include "Sprite.h"
#include "BodyDimensions.h"
class BodyBase : public Sprite 
{
    public:
        BodyBase(BodyDimensions& dimensions);
        void Initialise() override;
        int GetFrame() const;
        void SetRotation(float rotation);
        float GetFrameWidth() const;
        float GetFrameHeight() const;
    
    private:
        BodyDimensions& dimensions;
};
