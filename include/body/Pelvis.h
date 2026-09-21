#pragma once
#include "body/Legs/Legs.h"
#include "Shape.h"
#include "BodyDimensions.h"
class Pelvis : Shape
{
    public:
        Pelvis(BodyDimensions& dimensions);
        void Initialise() override;
        void Shutdown();
        
        void Update(float dt);
        void Draw() const;
        
        void SetTransform(MyTransform parentTransform);

    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset = {};
        Legs legs;
};
