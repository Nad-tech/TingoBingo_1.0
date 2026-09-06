#pragma once

#include "Sprite.h"
#include "raylib.h"

class Nose : public Sprite
{
    public:
        void Initialise() override;
        void Update(float dt) override;
        void Draw() const override;
        void SetBodyHeadDimensions(
            float bwidth, 
            float bHeigh, 
            float hWidth, 
            float hHeight
        );

    private:
        float bodyWidth = 0.0f;
        float bodyHeight = 0.0f;
        float headWidth = 0.0f;
        float headHeight = 0.0f;
        float localRotation = 0.0f;
}; 
