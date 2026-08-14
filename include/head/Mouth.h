#pragma once

#include "Sprite.h"
#include "Emotion.h"

class Mouth : public Sprite
{
    public:
        void Initialise() override;
        void UpdateMouth(float dt, bool speaking, Emotion emotion);
    
        void SetIdle();
        void SetHappy();

    private:
        int frame = 0;
        float frameTimer = 0.0f;
        const float FRAME_DURATION = 0.3f;
};