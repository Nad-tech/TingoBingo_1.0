#pragma once

#include "Sprite.h"
#include "Knee.h"
#include "BodyDimensions.h"

#include <string>

class Thigh : public Sprite
{
    public:
        Thigh(BodyDimensions& dimensions);
        void Initialise() override;
        int GetFrame() const;
        void SetRotation(float rotation);

    private:
        BodyDimensions& dimensions;
        std::string side;
        Knee knee;
};