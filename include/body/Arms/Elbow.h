#pragma once

#include "Sprite.h"
#include "ForeArm.h"

#include <string>

class Elbow : public Sprite
{
    public:
        void Initialise() override;
        void Update(float dt) override;
        void Draw() const override;
        
        int GetFrame() const;
        
        void SetRotation(float rotation);
        void SetBodyDimensions(float width, float height, std::string side);

    private:
        Vector2 localPositionOffset = {0, 0};
        float localRotation = 0.0f;
        float homeRotation = 0.0f;
        float bodyWidth = 0;
        float bodyHeight = 0;
        std::string side = "";

        ForeArm leftForeArm;
        ForeArm rightForeArm;
};