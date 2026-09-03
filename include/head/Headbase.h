#pragma once

#include "Sprite.h"

class Headbase : public Sprite 
{
    public:
        void Initialise() override;
        int GetFrame() const;
        void SetRotation(float rotation);
        void SetBodyDimensions(float width, float height);
        float GetFrameWidth() const;
        float GetFrameHeight() const;

    private:
        float bodyWidth;
        float bodyHeight;
};
