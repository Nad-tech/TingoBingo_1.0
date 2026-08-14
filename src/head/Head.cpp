//====================================================
// Head.cpp
//
// Coordinates all of the robot's head components.
//
// The Head class owns the individual facial features
// (head base, eyes, mouth, ears, antenna, nose,
// eyebrows and pupils) and keeps them synchronised by
// updating, drawing, positioning and rotating them as
// a single unit.
//
// It also controls the head's idle animations,
// including bobbing and wiggling.
//====================================================

#include "head/Head.h"
#include <cmath>
#include "Emotion.h"

// Initialise the head's transform and idle animation state.
Head::Head() :
    rotation(0.0f),
    scale(0.0f),

    homeRotation(rotation),
    headWiggleTimer(0.0f),
    headWiggleAmplitude(0.0f),
    headWiggling(false),
    nextHeadWiggle((float)GetRandomValue(5, 7)),
    headWiggleFrequency(0.0f),

    headBobOffset({0.0f, 0.0f}),
    headBobScale(7.0f),
    headBobAngle(0.0f),
    headBobDirection(1.0f),
    randomHeadBobSignTimer((float)GetRandomValue(5, 10)),
    headBobRadiusX(GetRandomValue(3, 8)),
    headBobRadiusY(GetRandomValue(2, 6)),
    headBobSpeed(GetRandomValue(6, 14) / 10.0f)
{
}

// Initialise every component that makes up the robot's head.
void Head::Initialise()
{
    headBase.Initialise();
    antenna.Initialise();
    ears.Initialise();
    eyebrows.Initialise();
    eyes.Initialise();
    mouth.Initialise();
    nose.Initialise();
    pupils.Initialise();
}

// Release resources used by each head component.
void Head::Shutdown()
{
    headBase.Shutdown();
    antenna.Shutdown();
    ears.Shutdown();
    eyebrows.Shutdown();
    eyes.Shutdown();
    mouth.Shutdown();
    nose.Shutdown();
    pupils.Shutdown();
}

// Update every animated head component.
void Head::Update(float dt, bool speaking, Emotion emotion)
{
    headBase.Update(dt);
    antenna.Update(dt);
    ears.Update(dt);
    eyebrows.UpdateEyebrows(dt, speaking, emotion);
    eyes.Update(dt);
    mouth.UpdateMouth(dt, speaking, emotion);
    nose.Update(dt);
    pupils.Update(dt);

    PlayIdleHeadTransform(dt);
}

void Head::Draw() const
{
    // Draw the full face only when the head is facing forward.
    // During head rotation the facial features are already
    // baked into the head sprite.
    if (IsFrontFacing())
    {
        ears.Draw();
        headBase.Draw();
        eyes.Draw();
        mouth.Draw();
        nose.Draw();
        eyebrows.Draw();
        antenna.Draw();
        pupils.Draw();
    }
    else
    {
        headBase.Draw();
    }
}

// Set the head's home position and apply it to every component.
void Head::SetPosition(Vector2 position)
{
    this->homePosition = position;
    ApplyPosition(position);
}

// Move every head component to the same world position.
void Head::ApplyPosition(Vector2 position)
{
    this->position = position;

    headBase.SetPosition(position);
    antenna.SetPosition(position);
    ears.SetPosition(position);
    eyebrows.SetPosition(position);
    eyes.SetPosition(position);
    mouth.SetPosition(position);
    nose.SetPosition(position);
    pupils.SetPosition(position);
}

Vector2 Head::GetPosition() const
{
    return position;
}

// Rotate the head one frame to the left.
void Head::RotateLeft()
{
    headBase.RotateLeft();
}

// Rotate the head one frame to the right.
void Head::RotateRight()
{
    headBase.RotateRight();
}

// Return the head to its forward-facing position.
void Head::ReturnToCentre()
{
    headBase.ReturnToCentre();
}

// Returns true when the front-facing head sprite is active.
bool Head::IsFrontFacing() const
{
    return headBase.GetFrame() == 0;
}

void Head::PlayIdleAntennaAnimation()
{
    antenna.PlayWiggle();
}

void Head::PlayIdleEarsAnimation()
{
    ears.PlayWiggle();
}

void Head::PlayIdleEyesAnimation()
{
    eyes.PlayBlink();
}

void Head::PlayIdleMouthAnimation()
{
    mouth.SetIdle();
}

void Head::PlayHappyMouthAnimation()
{
    mouth.SetHappy();
}

void Head::PlayIdleNoseAnimation()
{
    nose.PlayWiggle();
}

// Set the head's home rotation.
void Head::SetRotation(float rotation)
{
    homeRotation = rotation;
    ApplyRotation(rotation);
}

// Apply the current rotation to every head component.
void Head::ApplyRotation(float rotation)
{
    this->rotation = rotation;

    headBase.SetRotation(rotation);
    antenna.SetRotation(rotation);
    ears.SetRotation(rotation);
    eyebrows.SetRotation(rotation);
    eyes.SetRotation(rotation);
    mouth.SetRotation(rotation);
    nose.SetRotation(rotation);
    pupils.SetRotation(rotation);
}

// Play the head's idle movement by combining
// bobbing and rotation animations.
void Head::PlayIdleHeadTransform(float dt)
{
    PlayHeadBob(dt);
    ApplyPosition(position);

    PlayHeadWiggle(dt);
    ApplyRotation(rotation);
}

// Randomly play a damped side-to-side wiggle.
void Head::PlayHeadWiggle(float dt)
{
    nextHeadWiggle -= dt;

    if (nextHeadWiggle <= 0.0f && !headWiggling)
    {
        headWiggling = true;
        headWiggleTimer = 0.0f;
        headWiggleAmplitude = (float)GetRandomValue(10, 20);
        nextHeadWiggle = (float)GetRandomValue(5, 7);
        headWiggleFrequency = (float)GetRandomValue(10, 40);
    }

    if (headWiggling)
    {
        headWiggleTimer += dt;

        rotation = sin(headWiggleTimer * headWiggleFrequency) * headWiggleAmplitude;

        // Gradually reduce the wiggle until the head settles.
        headWiggleAmplitude -= 8.0f * dt;

        if (headWiggleAmplitude <= 0.0f)
        {
            headWiggling = false;
            rotation = homeRotation;
        }
    }
}

// Move the head in a slow, organic elliptical motion.
void Head::PlayHeadBob(float dt)
{
    headBobAngle += dt * headBobSpeed * headBobDirection;

    randomHeadBobSignTimer -= dt;

    // Periodically randomise the bobbing direction and movement.
    if (randomHeadBobSignTimer <= 0)
    {
        headBobDirection *= -1;
        randomHeadBobSignTimer = (float)GetRandomValue(5, 10);
        headBobRadiusX = GetRandomValue(3, 8);
        headBobRadiusY = GetRandomValue(2, 6);
        headBobSpeed = GetRandomValue(6, 14) / 10.0f;
    }

    headBobOffset.x = cos(headBobAngle) * headBobRadiusX;
    headBobOffset.y = sin(headBobAngle) * headBobRadiusY;

    position.x = homePosition.x + headBobOffset.x;
    position.y = homePosition.y + headBobOffset.y;
}

// Rotate the pupils to look towards the given point.
void Head::LookAt(Vector2 point)
{
    pupils.LookAt(point);
}