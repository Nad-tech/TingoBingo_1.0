#pragma once

#include "Sprite.h"

class BodyBase : public Sprite 
{
    public:
        void Initialise() override;
        int GetFrame() const;
        void SetRotation(float rotation);
        float GetFrameWidth() const;
        float GetFrameHeight() const;
};
