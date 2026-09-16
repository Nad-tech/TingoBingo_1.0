#pragma once

#include "Sprite.h"
#include "Emotion.h"
#include "BodyDimensions.h"

class Mouth : public Sprite
{
    public:
        Mouth(BodyDimensions& dimensions);
        void Initialise() override;
        void UpdateMouth(float dt, bool speaking, Emotion emotion);

    private:
        BodyDimensions& dimensions;

        int frame = 0;
        float frameTimer = 0.0f;
        const float FRAME_DURATION = 0.3f;

        Vector2 localPositionOffset = {};
        float mouthDisplayOffset = 28.0f;
};