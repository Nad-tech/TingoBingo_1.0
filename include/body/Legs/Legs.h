#pragma once

#include "body/Legs/Thigh.h"

class Legs
{
    public:
        void Initialise();
        void Shutdown();
        void Update(float dt);
        void Draw() const;
        void SetAnchorPoint(Vector2 anchorPoint);
        void SetRotation(float rotation);
        void SetBodyDimension(float bodyWidth, float bodyHeight);

    private:
        Thigh rightThigh;
        Thigh leftThigh;
};