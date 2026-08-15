#pragma once

#include "raylib.h"
#include "head/Antenna.h"
#include "head/Ears.h"
#include "head/Eyebrows.h"
#include "head/Mouth.h"
#include "head/Eyes.h"
#include "head/Headbase.h"
#include "head/Nose.h"
#include "head/Pupils.h"
#include "Emotion.h"

class Head
{
    public:
        Head();
        void Initialise();
        void Shutdown();

        void Update(float dt, bool speaking, Emotion emotion);
        void Draw() const;

        void SetPosition(Vector2 position);
        void ApplyPosition(Vector2 position);
        Vector2 GetPosition() const;
        
        void SetRotation(float rotation);
        void ApplyRotation(float rotation);
        float GetRotation();

        void RotateLeft();
        void RotateRight();
        void ReturnToCentre();
        bool IsFrontFacing() const;

        void PlayIdleEyesAnimation();
        void PlayIdleNoseAnimation();
        void PlayIdleHeadTransform(float dt);
        void PlayHeadWiggle(float dt);
        void PlayHeadBob(float dt);

        void LookAt(Vector2 point);

    private:
        Vector2 position;
    
        float rotation;
        float scale;
          
        float homeRotation;
        float headWiggleTimer;
        float headWiggleAmplitude;
        bool headWiggling;
        float nextHeadWiggle;
        float headWiggleFrequency;

        Vector2 headBobOffset;
        float headBobScale;
        float headBobAngle;
        float headBobDirection;
        float randomHeadBobSignTimer;
        float headBobRadiusX;
        float headBobRadiusY;
        float headBobSpeed;
        Vector2 homePosition;

        Headbase headBase;
        Eyes eyes;
        Antenna antenna;
        Ears ears;
        Eyebrows eyebrows;
        Mouth mouth;
        Nose nose;
        Pupils pupils;
};