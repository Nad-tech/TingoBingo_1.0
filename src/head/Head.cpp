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

#include "Body/Head/Head.h"
#include <cmath>
#include "Emotion.h"

// Initialise the head's transform and idle animation state.
Head::Head(BodyDimensions& dimensions) :
    dimensions(dimensions),
    headBase(dimensions),
    eyes(dimensions),
    antenna(dimensions),
    ears(dimensions),
    eyebrows(dimensions),
    mouth(dimensions),
    nose(dimensions)
{
}

// Initialise every component that makes up the robot's head.
void Head::Initialise()
{
    headBase.Initialise();
    positionOffset = {
        0,
        dimensions.neckHeight / 2.0f + dimensions.headHeight / 2.0f  
    };

    antenna.Initialise();
    ears.Initialise();
    eyebrows.Initialise();
    eyes.Initialise();
    mouth.Initialise();
    nose.Initialise();
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
}

// Update every animated head component.
void Head::Update(float dt, bool speaking, Emotion emotion)
{
    headBase.Update(dt);
    antenna.Update(dt);
    ears.Update(dt);
    eyebrows.Update(dt, speaking, emotion);
    eyes.Update(dt);
    mouth.UpdateMouth(dt, speaking, emotion);
    nose.Update(dt);
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
}

void Head::SetTransform(MyTransform parentTransform)
{
    transform.position =
    {
        parentTransform.position.x + positionOffset.x,
        parentTransform.position.y + positionOffset.y
    };

    transform.pivot =
    {
        0,
        -positionOffset.y - dimensions.bodyHeight / 2.0f
    };
    
    transform.rotation = parentTransform.rotation;
    transform.scale = parentTransform.scale;

    headBase.SetTransform(transform);
    eyes.SetTransform(transform);
    eyebrows.SetTransform(transform);
    ears.SetTransform(transform);
    antenna.SetTransform(transform);
    nose.SetTransform(transform);
    mouth.SetTransform(transform);
}

void Head::LookAt(Vector2 point)
{
    eyes.GetPupils().LookAt(point);
}

void Head::LookForward()
{
    eyes.GetPupils().LookForward();
}