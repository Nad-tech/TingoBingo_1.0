#pragma once

#include "body/Legs/Thigh.h"
#include "BodyDimensions.h"
#include "Shape.h"

class Legs : Shape
{
    public:
        Legs(BodyDimensions& dimensions);
        void Initialise();
        void Shutdown();
        void Update(float dt);
        void Draw() const;
        void SetAnchorPoint(Vector2 anchorPoint);
        void SetRotation(float rotation);

    private:
        BodyDimensions& dimensions;
        Thigh rightThigh;
        Thigh leftThigh;
};