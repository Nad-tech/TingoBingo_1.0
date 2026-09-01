#pragma once

#include "raylib.h"
#include "head/Antenna.h"
#include "head/Ears.h"
#include "head/Eyebrows.h"
#include "head/Mouth.h"
#include "head/Eyes.h"
#include "head/Headbase.h"
#include "head/Nose.h"
#include "head/Pupils.h"
#include "Emotion.h"


//====================================================
// Head
//
// Controls the complete robot head.
//
// Head owns all of the individual head components and
// keeps them synchronised so they behave as one unit.
//
// Facial features such as the eyes, mouth, eyebrows
// and pupils can animate independently while the
// Headbase handles the main head orientation.
//====================================================

class Head
{
public:

    // Initialise the head's transform and idle
    // animation state.
    Head();


    // Load and release all head component resources.
    void Initialise();
    void Shutdown();


    // Update all head components and their animations.
    //
    // speaking and emotion are passed to the facial
    // components so they can respond to the robot's
    // current behaviour.
    void Update(float dt, bool speaking, Emotion emotion);

    // Draw the complete head.
    void Draw() const;


    //================================================
    // Position
    //================================================

    // Set the head's world position.
    void SetPosition(Vector2 position);

    // Apply a position to all head components.
    void ApplyPosition(Vector2 position);

    // Return the head's current position.
    Vector2 GetPosition();


    //================================================
    // Rotation
    //================================================

    // Set the head's rotation.
    void SetRotation(float rotation);

    // Apply a rotation to all head components.
    void ApplyRotation(float rotation);

    // Return the current head rotation.
    float GetRotation();

    //================================================
    // Idle Animation
    //================================================

    // Update the combined idle head movement.
    //void PlayIdleHeadTransform(float dt);

    // Play the random side-to-side head wiggle.
    //void PlayHeadWiggle(float dt);

    // Play the slow, organic head bob.
    //void PlayHeadBob(float dt);


    //================================================
    // Eye Direction
    //================================================

    // Make the pupils look towards a specific point.
    void LookAt(Vector2 point);

    // Return the pupils to their forward-facing position.
    void LookForward();


private:

    // Current world position of the head.
    Vector2 position;

    // Current visual rotation and scale of the head.
    float rotation;
    float scale;

    //================================================
    // Head Components
    //================================================

    // Main head sprite. Contains the different head
    // orientations.
    Headbase headBase;

    // Independently animated facial components.
    Eyes eyes;
    Antenna antenna;
    Ears ears;
    Eyebrows eyebrows;
    Mouth mouth;
    Nose nose;
    Pupils pupils;
};