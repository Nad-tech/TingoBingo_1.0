#pragma once

#include "Body/Head/Head.h"
#include "Sprite.h"

#include "Emotion.h"

class Neck : public Sprite
{
    public:
        void Initialise() override;
        void Update(float dt, bool speaking, Emotion emotion);
        void Draw() const;
        void SetRotation(float rotation);
        void SetBodyDimensions(float bW, float bH);
        void SetAnchorPoint(Vector2 anchorPoint);
        Head& GetHead();
        void Shutdown();
    
    private:
        Head head;
        Vector2 localPositionOffset = {};
        float bodyWidth = 0;
        float bodyHeight = 0;

        const int NECK_WIDTH = 50;
        const int NECK_HEIGHT = 50;
};