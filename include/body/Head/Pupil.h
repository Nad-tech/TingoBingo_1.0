#pragma once

#include "Sprite.h"
#include <string>
#include "BodyDimensions.h"

class Pupil : public Sprite
{
    public:
        Pupil(BodyDimensions& dimensions);
        void Initialise() override;
        void Update(float dt) override;
        void SetSide(std::string side);
        float GetSideOffset();

    private:
        BodyDimensions& dimensions;

        std::string side; // "left" or "right"
        float sideOffset = 40;
};