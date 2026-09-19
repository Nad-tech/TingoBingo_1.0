#pragma once

#include "Sprite.h"
#include "ForeArm.h"
#include "BodyDimensions.h"

#include <string>

class Elbow : public Sprite
{
    public:
        Elbow(BodyDimensions& dimensions, std::string side);
        void Initialise() override;
        void Update(float dt) override;
        void Draw() const override;
        
        int GetFrame() const;
        
        void SetRotation(float rotation);

    private:
        BodyDimensions& dimensions;
        float localRotation = 0.0f;
        float homeRotation = 0.0f;
        std::string side = "";

        ForeArm foreArm;
};