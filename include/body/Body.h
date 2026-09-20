#pragma once

#include "raylib.h"
#include "Emotion.h"
#include "BodyBase.h"
#include "Body/Arms/Arms.h"
#include "Body/Pelvis.h"
#include "Body/Head/Head.h"
#include "Body/Neck.h"
#include "BodyDimensions.h"
#include "MyTransform.h"


class Body
{
public:
    Body(BodyDimensions& dimensions);
    void Initialise();
    void Shutdown();
    
    void Update(float dt, bool speaking, Emotion emotion);
    void Draw() const;
    
    void SetTransform(MyTransform transform);
    
    Head& GetHead();
    
    void PlayIdleBodyTransform(float dt);
    void PlayBodyWiggle(float dt);
    void PlayBodyBob(float dt);
    //void SwingArm(std::string side, bool swing);

private:
    BodyDimensions &dimensions;
    MyTransform transform;
    MyTransform homeTransform;
    BodyBase bodyBase;
    Neck neck;
    Pelvis pelvis;
    Arms arms;
    
    //================================================
    // Body Wiggle State
    //================================================

    float bodyWiggleTimer;
    float bodyWiggleAmplitude;
    bool bodyWiggling;
    float nextBodyWiggle;
    float bodyWiggleFrequency;

    //================================================
    // Body Bob State
    //================================================

    Vector2 bodyBobOffset;
    float bodyBobScale;
    float bodyBobAngle;
    float bodyBobDirection;
    float randomBodyBobSignTimer;
    float bodyBobRadiusX;
    float bodyBobRadiusY;
    float bodyBobSpeed;
};