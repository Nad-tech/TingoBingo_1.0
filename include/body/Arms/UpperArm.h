#pragma once
#include <string>

#include "Sprite.h"
#include "Body/Arms/Elbow.h"
#include "BodyDimensions.h"

class UpperArm : public Sprite
{
    public:
        UpperArm(BodyDimensions& dimensions, std::string side);

        void Initialise() override;
        void Update(float dt) override;
        void Draw() const override;
        
        int GetFrame() const;
        
        void SetRotation(float rotation);

        void SwingArm(float dt, float swingMinAngle, float swingMaxAngle);

    private:
        BodyDimensions& dimensions;
        Vector2 armAnchorPosition;
        float localRotation = 0.0f;
        std::string side = "";

        const float SWING_MIN = 0.0f;
        const float SWING_MAX = 180.0f;
        const float SWING_SPEED = 1.0f;
        float swingTime = 0;

        Elbow elbow;
};