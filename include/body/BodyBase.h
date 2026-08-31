#pragma once

#include "Sprite.h"

class BodyBase : public Sprite 
{
    public:
        void Initialise() override;
        void RotateLeft();
        void RotateRight();
        void ReturnToCentre();
        int GetFrame() const;
        void SetRotation(float rotation);
};
