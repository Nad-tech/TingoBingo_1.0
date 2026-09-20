#pragma once

#include "Sprite.h"
#include "BodyDimensions.h"
#include "Pupils.h"

class Eyes : public Sprite
{
    public:
        Eyes(BodyDimensions& dimensions);
        
        void Initialise() override;
        void ShutDown();

        void Update(float dt) override;
        void Draw() const;

        void SetTransform(MyTransform parentTransform);

        Pupils& GetPupils();

        void LookAt(Vector2 point);
        void LookForward();

    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;
        Pupils pupils;

        // TODO: make pupils child of Eyes
        float idleAnimationTimer = 0.0f;
        float nextIdleAnimation = 0.0f;
}; 
