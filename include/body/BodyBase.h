#pragma once

#include "Sprite.h"
#include "BodyDimensions.h"
#include "MyTransform.h"
class BodyBase : public Sprite 
{
    public:
        BodyBase(BodyDimensions& dimensions);
        void Initialise() override;
        int GetFrame() const;
        void SetRotation(float rotation);
        void SetTransform(MyTransform transform);
    
    private:
        BodyDimensions& dimensions;
        MyTransform transform;

};
