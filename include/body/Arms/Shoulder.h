#pragma once 

#include "Sprite.h"
#include "UpperArm.h"
#include "BodyDimensions.h"

class Shoulder : public Sprite
{
    public:
        Shoulder(BodyDimensions& dimensions, std::string side);

        void Initialise() override;
        void Update(float dt) override;
        void Draw() const override;
        
        int GetFrame() const;
        void SetAnchorPoint(Vector2 anchorPoint);
        void SetRotation(float rotation);

        void SwingArm(float dt, float swingMinAngle, float swingMaxAngle);

    private:
        BodyDimensions& dimensions;
        Vector2 armAnchorPosition;

        std::string side = "";
        UpperArm upperArm;
};