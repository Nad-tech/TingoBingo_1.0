#pragma once

#include "Sprite.h"
#include <string>
class Arm : public Sprite
{
    public:
        void Initialise() override;
        int GetFrame() const;
        void SetRotation(float rotation);
        void SetBodyDimensions(float width, float height, std::string side);

    private:
        float bodyWidth;
        float bodyHeight;
        std::string side;
};