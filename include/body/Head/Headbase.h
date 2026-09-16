#pragma once

#include "Sprite.h"
#include "BodyDimensions.h"

class Headbase : public Sprite 
{
    public:
        Headbase(BodyDimensions& dimensions);
        void Initialise() override;
        int GetFrame() const;
        void SetRotation(float rotation);
        Vector2 GetWorldPosition() const;
        
    private:
        BodyDimensions& dimensions;
};
