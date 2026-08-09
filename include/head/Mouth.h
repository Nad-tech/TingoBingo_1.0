#pragma once

#include "Sprite.h"

class Mouth : public Sprite
{
    public:
        void Initialise() override;
        void Update(float dt, bool speaking);
    
        void PlayIdleMouth();

    private:
        int frame = 0;
        float frameTimer = 0.0f;
        const float FRAME_DURATION = 0.3f;
};