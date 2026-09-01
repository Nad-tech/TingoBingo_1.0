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
    scale(0.0f)
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

    //PlayIdleHeadTransform(dt);
}

void Head::Draw() const
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

// Set the head's home position and apply it to every component.
void Head::SetPosition(Vector2 position)
{
    //this->homePosition = position;
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

Vector2 Head::GetPosition()
{
    return position;
}

// Set the head's home rotation.
void Head::SetRotation(float rotation)
{
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

float Head::GetRotation()
{
    return rotation;
}

// Rotate the pupils to look towards the given point.
void Head::LookAt(Vector2 point)
{
    pupils.LookAt(point);
}

void Head::LookForward()
{
    pupils.LookForward();
}