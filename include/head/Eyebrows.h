#pragma once

#include "Sprite.h"
#include "Emotion.h"

class Eyebrows : public Sprite
{
    public:
        void Initialise() override;
        void UpdateEyebrows(float dt, bool speaking, Emotion emotion);
    
        void SetIdle();
        void SetHappy();

    private:
};