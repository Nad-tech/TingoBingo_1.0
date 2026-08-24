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
};