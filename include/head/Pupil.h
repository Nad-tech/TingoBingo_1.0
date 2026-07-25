#pragma once

#include "Sprite.h"

class Pupil : public Sprite
{
    public:
        void Initialise() override;
        void Update(float dt) override;
};