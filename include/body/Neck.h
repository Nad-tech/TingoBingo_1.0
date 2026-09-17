#pragma once

#include "Body/Head/Head.h"
#include "Sprite.h"

#include "Emotion.h"
#include "BodyDimensions.h"

class Neck : public Sprite
{
    public:
        Neck(BodyDimensions& dimensions);
        void Initialise() override;
        void Update(float dt, bool speaking, Emotion emotion);
        void Draw() const;
        void SetRotation(float rotation);
        void SetAnchorPoint(Vector2 anchorPoint);
        Head& GetHead();
        void Shutdown();
    
    private:
        BodyDimensions& dimensions;
        Head head;
};