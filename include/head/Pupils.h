#pragma once

#include "head/Pupil.h"
#include "raylib.h"
#include "Constants.h"


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

    // Load the pupil resources.
    void Initialise();

    // Release the pupil resources.
    void Shutdown();

    // Update both pupils.
    void Update(float dt);

    // Draw both pupils.
    void Draw() const;


    // Set the anchor point of both pupils.
    void SetAnchorPoint(Vector2 anchorPoint);

    // Set the rotation of both pupils.
    void SetRotation(float rotation);


    // Rotate a vector around the anchor point.
    //
    // Used when calculating pupil positions relative
    // to the head's rotation.
    Vector2 RotateVector(Vector2 v, float rotation);


    // Make both pupils look towards a target point.
    void LookAt(Vector2 point);

    // Return both pupils to their normal forward-facing
    // anchor point.
    void LookForward();

private:
    // The two independently rendered pupils.
    Pupil leftPupil;
    Pupil rightPupil;

    // Maximum distance a pupil can move from the centre of the eye.
    const float LOOK_DISTANCE = 10.0f;

    Vector2 leftEyeOffset  = {-33.5f * SCALE, 10.5f * SCALE};
    Vector2 rightEyeOffset = { 40.5f * SCALE, 10.5f * SCALE};

    // Current anchor point of the head in world space.
    Vector2 headAnchorPoint = {0, 0};

    // Current look offsets applied to each pupil.
    Vector2 leftLookOffset  = {0.0f, 0.0f};
    Vector2 rightLookOffset = {0.0f, 0.0f};
};