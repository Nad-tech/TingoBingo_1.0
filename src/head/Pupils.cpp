//====================================================
// Pupils.cpp
//
// Controls both of the robot's pupils.
//
// This class keeps the pupils positioned inside the
// eyes and moves them towards a target point to give
// the illusion that the robot is looking around.
//====================================================

#include "head/Pupils.h"
#include "raylib.h"
#include "cmath"
#include "raymath.h"


//These globals should be memeber variables in pupils.h
//especially if im going to have more than one tingo 
//keeping them here means they wont have their own eye positions they will share
// Default pupil positions relative to the centre of the head.
Vector2 leftEyeOffset  = {-67.0f, 21.0f};
Vector2 rightEyeOffset = { 81.0f, 21.0f};

// Current position of the head in world space.
Vector2 headPosition = {0, 0};

// Current look offsets applied to each pupil.
Vector2 leftLookOffset  = {0.0f, 0.0f};
Vector2 rightLookOffset = {0.0f, 0.0f};

// Maximum distance a pupil can move from the centre of the eye.
const float LOOK_DISTANCE = 15.0f;

// Initialise both pupil sprites.
void Pupils::Initialise()
{
    leftPupil.Initialise();
    rightPupil.Initialise();
}

// Release resources used by both pupils.
void Pupils::Shutdown()
{
    leftPupil.Shutdown();
    rightPupil.Shutdown();
}

// Update both pupil animations.
void Pupils::Update(float dt)
{
    leftPupil.Update(dt);
    rightPupil.Update(dt);
}

// Draw both pupils.
void Pupils::Draw() const
{
    leftPupil.Draw();
    rightPupil.Draw();
}

// Position both pupils relative to the head.
void Pupils::SetPosition(Vector2 position)
{
    headPosition = position;

    leftPupil.SetPosition(
    {
        position.x + leftEyeOffset.x,
        position.y + leftEyeOffset.y
    });

    rightPupil.SetPosition(
    {
        position.x + rightEyeOffset.x,
        position.y + rightEyeOffset.y
    });
}

// Rotate a vector around the origin.
Vector2 Pupils::RotateVector(Vector2 v, float rotation)
{
    float r = rotation * DEG2RAD;

    return
    {
        v.x * cosf(r) - v.y * sinf(r),
        v.x * sinf(r) + v.y * cosf(r)
    };
}

// Rotate the pupils so they remain aligned with the head.
void Pupils::SetRotation(float rotation)
{
    Vector2 rotatedLeft =
        RotateVector(Vector2Add(leftEyeOffset, leftLookOffset), rotation);

    Vector2 rotatedRight =
        RotateVector(Vector2Add(rightEyeOffset, rightLookOffset), rotation);

    leftPupil.SetPosition(
    {
        headPosition.x + rotatedLeft.x,
        headPosition.y + rotatedLeft.y
    });

    rightPupil.SetPosition(
    {
        headPosition.x + rotatedRight.x,
        headPosition.y + rotatedRight.y
    });

    leftPupil.SetRotation(rotation);
    rightPupil.SetRotation(rotation);
}

// Move the pupils towards a target point while limiting
// how far they can travel within the eye.
void Pupils::LookAt(Vector2 point)
{
    Vector2 leftEyeCentre =
    {
        headPosition.x + leftEyeOffset.x,
        headPosition.y + leftEyeOffset.y
    };

    Vector2 rightEyeCentre =
    {
        headPosition.x + rightEyeOffset.x,
        headPosition.y + rightEyeOffset.y
    };

    // Calculate the direction from each eye to the target.
    Vector2 leftDirection =
    {
        point.x - leftEyeCentre.x,
        point.y - leftEyeCentre.y
    };

    Vector2 rightDirection =
    {
        point.x - rightEyeCentre.x,
        point.y - rightEyeCentre.y
    };

    leftDirection = Vector2Normalize(leftDirection);
    rightDirection = Vector2Normalize(rightDirection);

    // Convert the direction into a small movement offset.
    leftLookOffset =
    {
        leftDirection.x * LOOK_DISTANCE,
        leftDirection.y * LOOK_DISTANCE
    };

    rightLookOffset =
    {
        rightDirection.x * LOOK_DISTANCE,
        rightDirection.y * LOOK_DISTANCE
    };
}

void Pupils::LookForward()
{
    leftLookOffset = {0.0f, 0.0f};
    rightLookOffset = {0.0f, 0.0f};

    leftPupil.SetPosition(
    {
        headPosition.x + leftEyeOffset.x,
        headPosition.y + leftEyeOffset.y
    });

    rightPupil.SetPosition(
    {
        headPosition.x + rightEyeOffset.x,
        headPosition.y + rightEyeOffset.y
    });
}
