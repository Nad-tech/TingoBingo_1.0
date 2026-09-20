#pragma once

#include "Body/Head/Pupil.h"
#include "raylib.h"
#include "Constants.h"
#include "BodyDimensions.h"
#include "MyTransform.h"


//====================================================
// Pupils
//
// Controls both of the robot's pupils as a pair.
//
// Pupils can be positioned and rotated together,
// while LookAt() and LookForward() control where
// Tingo's eyes are looking.
//====================================================

class Pupils
{
public:
    Pupils(BodyDimensions& dimensions);

    void Initialise();
    void Shutdown();

    void Update(float dt);
    void Draw() const;

    void SetTransform(MyTransform parentTransform);

    void SetRotation(float rotation);
    Vector2 RotateVector(Vector2 v, float rotation);

    void LookAt(Vector2 point);
    void LookForward();
    
private:
    BodyDimensions& dimensions;
    MyTransform transform;

    Pupil leftPupil;
    Pupil rightPupil;

    // Maximum distance a pupil can move from the centre of the eye.
    const float LOOK_DISTANCE = 10.0f;

    Vector2 leftLookOffset  = {0.0f, 0.0f};
    Vector2 rightLookOffset = {0.0f, 0.0f};
};