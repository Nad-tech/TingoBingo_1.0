#pragma once
#include "Sprite.h"

#include "Foot.h"
class Shin : public Sprite
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
        
        float bodyWidth = 0;
        float bodyHeight = 0;

        Foot leftFoot;
        Foot rightFoot;
};