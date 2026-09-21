//====================================================
// Pupils.cpp
//
// Controls both of the robot's pupils.
//
// This class keeps the pupils positioned inside the
// eyes and moves them towards a target point to give
// the illusion that the robot is looking around.
//====================================================

#include "Body/Head/Pupils.h"
#include "raylib.h"
#include "cmath"
#include "raymath.h"

Vector2 L;

Pupils::Pupils(BodyDimensions& dimensions) : 
    dimensions(dimensions),
    transform(),
    leftPupil(dimensions),
    rightPupil(dimensions)
{}

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
    DrawCircle(L.x, L.y, 50, RED);
}

// Set both pupil anchor points relative to the head.
void Pupils::SetTransform(MyTransform parentTransform)
{
    transform = parentTransform;

    leftPupil.SetTransform(parentTransform);
    rightPupil.SetTransform(parentTransform);

    SetRotation(transform.rotation);
}

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

    leftPupil.SetRotation(rotation);
    rightPupil.SetRotation(rotation);

    leftPupil.SetPosition(
    {
        transform.position.x + rotatedLeft.x,
        transform.position.y + rotatedLeft.y
    });

    rightPupil.SetPosition(
    {
        transform.position.x + rotatedRight.x,
        transform.position.y + rotatedRight.y
    });

}

// Move the pupils towards a target point while limiting
// how far they can travel within the eye.
void Pupils::LookAt(Vector2 point)
{
    float scale = transform.scale;

    Vector2 leftEyeCentre =
    {
        transform.position.x + leftPupil.GetSideOffset() * scale,
        transform.position.y -
        (dimensions.bodyHeight / 2 
        + dimensions.headHeight / 2 
        + dimensions.neckHeight 
        + dimensions.eyesYoffset) * scale

    };

    Vector2 rightEyeCentre =
    {
        transform.position.x - rightPupil.GetSideOffset() * scale,
        transform.position.y -  
        (dimensions.bodyHeight / 2 
        + dimensions.headHeight / 2 
        + dimensions.neckHeight 
        + dimensions.eyesYoffset) * scale
    };

    L = rightEyeCentre;

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

    SetRotation(transform.rotation);
}

void Pupils::LookForward()
{
    leftLookOffset = {0.0f, 0.0f};
    rightLookOffset = {0.0f, 0.0f};

    leftPupil.SetPosition(
    {
        transform.position.x,
        transform.position.y
    });

    rightPupil.SetPosition(
    {
        transform.position.x,
        transform.position.y
    });
}
