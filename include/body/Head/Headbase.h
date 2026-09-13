#pragma once

#include "Sprite.h"

class Headbase : public Sprite 
{
    public:
        void Initialise() override;
        int GetFrame() const;
        void SetRotation(float rotation);
        void SetBodyNeckDimensions(float bW, float bH, float nW, float nH);
        float GetFrameWidth() const;
        float GetFrameHeight() const;
        Vector2 GetWorldPosition() const;
        
    private:
        float bodyWidth;
        float bodyHeight;
        float neckWidth;
        float neckHeight;
};
