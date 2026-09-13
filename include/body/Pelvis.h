#pragma once
#include "body/Legs/Legs.h"
#include "Sprite.h"
class Pelvis : Sprite
{
    public:
        public:
        void Initialise() override;
        void Update(float dt) override;
        void Draw() const;
        void SetRotation(float rotation);
        void SetBodyDimensions(float bW, float bH);
        void SetAnchorPoint(Vector2 anchorPoint);
        void Shutdown();

    private:
        Vector2 localPositionOffset = {};
        float topOfHeadOffset = 46.0f;
        float bodyWidth = 0;
        float bodyHeight = 0;

    private:
        Legs legs;
};
