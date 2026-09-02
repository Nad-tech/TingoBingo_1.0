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
    
    void SetPosition(Vector2 position);
    
    void ApplyPosition(Vector2 position);

    Vector2 GetPosition() const;

    void SetRotation(float rotation);

    void ApplyRotation(float rotation);

    float GetRotation();

    void PlayIdleBodyTransform(float dt);

    void PlayBodyWiggle(float dt);

    void PlayBodyBob(float dt);

    Head& GetHead();
    
    Leg rightLeg;
    Leg leftLeg;
    Arm rightArm;
    Arm leftArm;

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

    Head head;

    BodyBase bodyBase;

    float armX = 165.0f; 
    float legX = 40.0f;
    float legY = 200.0f;
    
    Vector2 leftArmOffset = {-armX, 0};
    Vector2 rightArmOffset = {armX, 0};
    Vector2 leftLegOffset = {-legX, legY};
    Vector2 rightLegOffset = {legX, legY};

    Vector2 headOffset = {0.0f, 0.0f};
};