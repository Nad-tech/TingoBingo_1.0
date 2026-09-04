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

// Initialise both pupil sprites.
void Pupils::Initialise()
{
    leftPupil.SetSide("left");
    leftPupil.Initialise();
   
    rightPupil.SetSide("right");
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

// Set both pupil anchor points relative to the head.
void Pupils::SetAnchorPoint(Vector2 anchorPoint)
{
    headAnchorPoint = anchorPoint;

    leftPupil.SetAnchorPoint(
    {
        anchorPoint.x,
        anchorPoint.y
    });

    rightPupil.SetAnchorPoint(
    {
        anchorPoint.x,
        anchorPoint.y
    });
}

// Rotate an anchor offset around the anchor point.
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
        RotateVector(leftLookOffset, rotation);

    Vector2 rotatedRight =
        RotateVector(rightLookOffset, rotation);

    leftPupil.SetAnchorPoint(
    {
        headAnchorPoint.x + rotatedLeft.x,
        headAnchorPoint.y + rotatedLeft.y
    });

    rightPupil.SetAnchorPoint(
    {
        headAnchorPoint.x + rotatedRight.x,
        headAnchorPoint.y + rotatedRight.y
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
        headAnchorPoint.x,
        headAnchorPoint.y
    };

    Vector2 rightEyeCentre =
    {
        headAnchorPoint.x,
        headAnchorPoint.y
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

    leftPupil.SetAnchorPoint(
    {
        headAnchorPoint.x,
        headAnchorPoint.y
    });

    rightPupil.SetAnchorPoint(
    {
        headAnchorPoint.x,
        headAnchorPoint.y
    });
}

void Pupils::SetBodyHeadEyeOffsetDimensions(float bWidth, 
    float bHeight, 
    float hWidth, 
    float hHeight,
    float eyesYOffset
)
{
    leftPupil.SetBodyDimensions(bWidth, bHeight);
    rightPupil.SetBodyDimensions(bWidth, bHeight);
    leftPupil.SetHeadDimensions(hWidth, hHeight);
    rightPupil.SetHeadDimensions(hWidth, hHeight);
    leftPupil.SetEyesYOffset(eyesYOffset);
    rightPupil.SetEyesYOffset(eyesYOffset);
}