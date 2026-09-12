#pragma once

#include "Shoulder.h"

class Arms
{
    public:
        void Initialise();
        void Update(float dt);
        void Draw() const;
        void SetAnchorPoint(Vector2 anchorPoint);
        void SetRotation(float rotation);
        void SetBodyDimensions(float bodyWidth, float bodyHeight);
        void SwingArm(std::string side, bool swing);
        void Shutdown();

    private:
        Shoulder leftShoulder;
        Shoulder rightShoulder;

        bool swingLeftUpperArm = false;
        bool swingRightUpperArm = false;

        float bodyWidth;
        float bodyHeight;
};


