#pragma once

#include "Body/Head/Head.h"
#include "Shape.h"
#include "Emotion.h"
#include "BodyDimensions.h"
#include "MyTransform.h"

class Neck : public Shape
{
    public:
        Neck(BodyDimensions& dimensions);
        void Initialise() override;
        void Shutdown();
        
        void Update(float dt, bool speaking, Emotion emotion);
        void Draw() const override;
        
        void SetTransform(MyTransform parentTransform);
        
        Head& GetHead();
        
    private:
        Vector2 positionOffset;
        Head head;
};