#pragma once
#include <string>

#include "Sprite.h"
#include "ForeArm.h"

class UpperArm : public Sprite
{
    public:
        void Initialise() override;
        void Update(float dt) override;
        void Draw() const override;
        
        int GetFrame() const;
        
        void SetRotation(float rotation);
        void SetBodyDimensions(float width, float height, std::string side);

        void SwingArm(float dt, float swingMinAngle, float swingMaxAngle);

    private:
        Vector2 localPositionOffset = {0, 0};
        float localRotation = 0.0f;
        float homeRotation = 0.0f;
        float bodyWidth = 0;
        float bodyHeight = 0;
        std::string side = "";

        const float SWING_MIN = 0.0f;
        const float SWING_MAX = 180.0f;
        const float SWING_SPEED = 10.0f;
        float swingTime = 0;

        ForeArm leftForeArm;
        ForeArm rightForeArm;
};