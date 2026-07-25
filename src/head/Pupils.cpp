#include "head\Pupils.h"
#include "raylib.h"
#include "cmath"
#include "raymath.h"

Vector2 leftEyeOffset  = {-67.0f, 21.0f};
Vector2 rightEyeOffset = { 81.0f, 21.0f};
Vector2 headPosition = {0,0};

Vector2 leftLookOffset  = {0.0f, 0.0f};
Vector2 rightLookOffset = {0.0f, 0.0f};
const float LOOK_DISTANCE = 15.0f;

void Pupils::Initialise()
{
    leftPupil.Initialise();
    rightPupil.Initialise();
}

void Pupils::Shutdown()
{
    leftPupil.Shutdown();
    rightPupil.Shutdown();
}

void Pupils::Update(float dt)
{
    leftPupil.Update(dt);
    rightPupil.Update(dt);
}

void Pupils::Draw() const
{
    leftPupil.Draw();
    rightPupil.Draw();
}

void Pupils::SetPosition(Vector2 position)
{
    headPosition = position;

    leftPupil.SetPosition(
        {
            position.x + leftEyeOffset.x, position.y + leftEyeOffset.y
        });

    rightPupil.SetPosition(
        {
            position.x + rightEyeOffset.x, position.y + rightEyeOffset.y
        });
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

void Pupils::SetRotation(float rotation)
{
    Vector2 rotatedLeft  = RotateVector(Vector2Add(leftEyeOffset, leftLookOffset), rotation);
    Vector2 rotatedRight = RotateVector(Vector2Add(rightEyeOffset, rightLookOffset), rotation);

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