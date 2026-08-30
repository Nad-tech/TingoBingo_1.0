#pragma once

#include "head/Pupil.h"
#include "raylib.h"


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


    // Set the position of both pupils.
    void SetPosition(Vector2 position);

    // Set the rotation of both pupils.
    void SetRotation(float rotation);


    // Rotate a vector around the origin.
    //
    // Used when calculating pupil positions relative
    // to the head's rotation.
    Vector2 RotateVector(Vector2 v, float rotation);


    // Make both pupils look towards a target point.
    void LookAt(Vector2 point);

    // Return both pupils to their normal forward-facing
    // position.
    void LookForward();

private:
    // The two independently rendered pupils.
    Pupil leftPupil;
    Pupil rightPupil;

    // Maximum distance a pupil can move from the centre of the eye.
    const float LOOK_DISTANCE = 15.0f;

    Vector2 leftEyeOffset  = {-67.0f, 21.0f};
    Vector2 rightEyeOffset = { 81.0f, 21.0f};

    // Current position of the head in world space.
    Vector2 headPosition = {0, 0};

    // Current look offsets applied to each pupil.
    Vector2 leftLookOffset  = {0.0f, 0.0f};
    Vector2 rightLookOffset = {0.0f, 0.0f};
};