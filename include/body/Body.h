#pragma once

#include "raylib.h"
#include "Emotion.h"
#include "BodyBase.h"

class Body
{
public:

    Body();

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


    void PlayIdleBodyTransform(float dt);

    void PlayBodyWiggle(float dt);

    void PlayBodyBob(float dt);


private:
    Vector2 position;

    float rotation;
    float scale;
    float homeRotation;

    // Tracks the progress of the current wiggle.
    float bodyWiggleTimer;

    // Current strength of the wiggle.
    float bodyWiggleAmplitude;

    // True while a wiggle animation is active.
    bool bodyWiggling;

    // Time remaining before another wiggle can begin.
    float nextBodyWiggle;

    // Controls how quickly the wiggle oscillates.
    float bodyWiggleFrequency;


    //================================================
    // Body Bob State
    //================================================

    // Current positional offset produced by the bob.
    Vector2 bodyBobOffset;

    // Controls the scale of the bob movement.
    float bodyBobScale;

    // Current position within the bob's movement cycle.
    float bodyBobAngle;

    // Direction of the bobbing motion.
    float bodyBobDirection;

    // Time remaining before the bobbing direction
    // and movement parameters are randomised.
    float randomBodyBobSignTimer;

    // Horizontal and vertical size of the bob movement.
    float bodyBobRadiusX;
    float bodyBobRadiusY;

    // Speed of the bobbing motion.
    float bodyBobSpeed;

    // Position the body returns to after applying
    // its idle movement.
    Vector2 homePosition;

    BodyBase bodyBase;
};