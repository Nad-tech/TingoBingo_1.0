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
        float localRotation = 0.0f;
        float homeRotation = 0.0f;
        std::string side = "";

        const float SWING_MIN = 0.0f;
        const float SWING_MAX = 180.0f;
        const float SWING_SPEED = 10.0f;
        float swingTime = 0;

        Elbow leftElbow;
        Elbow rightElbow;
};