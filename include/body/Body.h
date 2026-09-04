#pragma once

#include "raylib.h"
#include "Emotion.h"
#include "BodyBase.h"
#include "Arm.h"
#include "Leg.h"
#include "head/Head.h"

class Body
{
public:

    Body();

    void Initialise();
    
    void Shutdown();
    
    void Update(float dt, bool speaking, Emotion emotion);

    void Draw() const;
    
    void SetAnchorPoint(Vector2 anchorPoint);
    
    void ApplyAnchorPoint(Vector2 anchorPoint);

    Vector2 GetAnchorPoint() const;

    void SetRotation(float rotation);

    void ApplyRotation(float rotation);

    float GetRotation();

    void PlayIdleBodyTransform(float dt);

    void PlayBodyWiggle(float dt);

    void PlayBodyBob(float dt);

    Head& GetHead();

private:
    Vector2 anchorPoint;

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

    // Current anchor-point position within the bob's movement cycle.
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

    // Anchor point the body returns to after applying
    // its idle movement.
    Vector2 homeAnchorPoint;

    BodyBase bodyBase;

    Head head;
    Leg rightLeg;
    Leg leftLeg;
    Arm rightArm;
    Arm leftArm;

    Vector2 leftArmOffset = {0, 0};
    Vector2 rightArmOffset = {0, 0};
    Vector2 leftLegOffset = {0, 0};
    Vector2 rightLegOffset = {0, 0};

    Vector2 headOffset = {0.0f, 0.0f};
};