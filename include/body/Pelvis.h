#pragma once
#include "body/Legs/Legs.h"
#include "Sprite.h"
#include "BodyDimensions.h"
class Pelvis : Sprite
{
    public:
        Pelvis(BodyDimensions& dimensions);
        void Initialise() override;
        void Update(float dt) override;
        void Draw() const;
        void SetRotation(float rotation);
        void SetAnchorPoint(Vector2 anchorPoint);
        void Shutdown();

    private:
        BodyDimensions& dimensions;
        Vector2 localPositionOffset = {};
        Legs legs;
};
