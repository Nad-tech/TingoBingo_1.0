#pragma once

#include "Sprite.h"

class Headbase : public Sprite 
{
    public:
        void Initialise() override;
        int GetFrame() const;
        void SetRotation(float rotation);
};
