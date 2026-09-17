#pragma once

#include "Shoulder.h"
#include "BodyDimensions.h"

class Arms
{
    public:
        Arms(BodyDimensions& dimensions);

        void Initialise();
        void Update(float dt);
        void Draw() const;
        void SetAnchorPoint(Vector2 anchorPoint);
        void SetRotation(float rotation);
        void SwingArm(std::string side, bool swing);
        void Shutdown();

    private:
        BodyDimensions& dimensions;

        Shoulder leftShoulder;
        Shoulder rightShoulder;

        bool swingLeftArm = false;
        bool swingRightArm = false;
};


