#pragma once

#include "SpritePart.h"

class Headbase : public SpritePart 
{
    public:
        void Initialise() override;
        void Update(float dt) override;
        void Draw() const override;
        void IncrementFrame();

    private:
        int frame;
        float frameTimer = 0.0f;
};
