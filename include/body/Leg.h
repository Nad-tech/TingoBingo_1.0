#pragma once

#include "Sprite.h"
#include <string>
class Leg : public Sprite
{
    public:
        void Initialise() override;
        int GetFrame() const;
        void SetRotation(float rotation);
        void SetBodyDimensions(float width, float height, const std::string& side);

    private:
        float bodyWidth;
        float bodyHeight;
        std::string side;
};