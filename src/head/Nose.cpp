//====================================================
// Nose.cpp
//
// Handles the robot's nose sprite and idle animations.
//
// The nose uses two levels of rotation:
//
// 1. Parent rotation:
//    The nose position rotates around the body/head
//    reference point, allowing it to follow the head
//    when the head rotates.
//
// 2. Local rotation:
//    The nose itself rotates around its own centre.
//
// The nose also has an independent horizontal wiggle
// animation. The wiggle modifies the nose's local
// local position offset while preserving its original position.
//
//====================================================

#include "Body/Head/Nose.h"
#include "Constants.h"
#include <iostream>
#include <cmath>

Nose::Nose(BodyDimensions& dimensions) : dimensions(dimensions)
{}

//====================================================
// Initialise
//====================================================
//
// Loads the nose texture and sets up its animation.
//
// The nose uses the anchor point supplied by the Head
// as its parent rotation reference.
//
// localPositionOffset stores the nose's position relative to
// that parent anchor point.
//
// homeAnchorPoint stores the original local offset.
// This gives the wiggle animation a fixed position to
// return to after the animation finishes.
//
//====================================================

void Nose::Initialise()
{
    // Load the nose texture.
    texture = LoadTexture(
        "assets/images/TingoBingo/head/nose.png"
    );

    //================================================
    // Sprite Sheet Layout
    //================================================

    // The nose currently consists of a single frame.
    const int COLUMNS = 1;
    const int ROWS = 1;

    // Calculate the dimensions of one animation frame.
    dimensions.noseWidth =
        texture.width / COLUMNS;

    dimensions.noseHeight =
        texture.height / ROWS;

    const int TOTAL_FRAMES =
        COLUMNS * ROWS;

    // Time between animation frames.
    const float FRAME_DURATION = 0.08f;

    // Initialise the animation system.
    animation.Initialise(
        dimensions.noseWidth,
        dimensions.noseHeight,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    positionOffset = {
        0,
        -slightPositionOffset
    };

    homePosition = positionOffset;
}

//====================================================
// Update
//====================================================
//
// Updates the base Sprite animation and the nose's
// independent idle animations.
//
// The nose has two independent idle behaviours:
//
// 1. Rotation:
//    Occasionally rotates the nose through 360 degrees.
//
// 2. Wiggle:
//    Occasionally moves the nose horizontally around
//    its original local anchor position.
//
// localRotation is independent of the parent's rotation.
//
// rotation:
//     Rotation inherited from the Head.
//
// localRotation:
//     Additional rotation belonging only to the nose.
//
//====================================================

void Nose::Update(float dt)
{
    // Update the base Sprite animation.
    Sprite::Update(dt);

    //================================================
    // Nose Rotation Idle Animation
    //================================================

    // Count down until the next nose rotation.
    nextNoseRotation -= dt;

    if (nextNoseRotation <= 0.0f && !noseRotating)
    {
        // Start a new nose rotation.
        noseRotating = true;

        // Reset the rotation timer.
        noseRotateTimer = 0.0f;

        // Randomise the delay before the following rotation.
        nextNoseRotation = (float)GetRandomValue(7, 12);
    }

    if (noseRotating)
    {
        // Track how long the rotation has been active.
        noseRotateTimer += dt;

        // Rotate the nose using a frame-rate independent
        // speed defined by LOCAL_ROTATION_SPEED.
        localRotation += LOCAL_ROTATION_SPEED * dt;

        // Once a complete 360-degree rotation is reached,
        // stop the idle animation and return to zero local
        // rotation.
        if (localRotation >= 360.0f)
        {
            noseRotating = false;
            localRotation = 0;
        }
    }

    //================================================
    // Nose Wiggle Idle Animation
    //================================================

    // Count down until the next nose wiggle.
    nextNoseWiggle -= dt;

    if (nextNoseWiggle <= 0.0f && !noseWiggling)
    {
        // Start a new wiggle.
        noseWiggling = true;

        // Reset the wiggle timer.
        noseWiggleTimer = 0.0f;

        // Randomise the delay before the following wiggle.
        nextNoseWiggle = (float)GetRandomValue(5, 7);

        // The original local parent position is already
        // stored in home position.
    }

    if (noseWiggling)
    {
        // Track how long the wiggle has been active.
        noseWiggleTimer += dt;

        // Calculate the horizontal wiggle using a sine wave.
        //
        // WIGGLE_SPEED controls how quickly the nose moves.
        // WIGGLE_AMOUNT controls how far it moves from
        // its original position.
        wiggleOffSetX =
            sinf(noseWiggleTimer * WIGGLE_SPEED) * WIGGLE_AMOUNT;

        // Apply the wiggle to the original LOCAL position.
        //
        // Using homeAnchorPoint as the starting position
        // prevents the wiggle from accumulating movement
        // from one frame to the next.
        positionOffset.x =
            homePosition.x + wiggleOffSetX;

        // The wiggle lasts for one second.
        if (noseWiggleTimer >= 1.0f)
        {
            // Stop the wiggle.
            noseWiggling = false;

            // Reset the wiggle state.
            noseWiggleTimer = 0.0f;
            wiggleOffSetX = 0.0f;

            // Restore the original LOCAL anchor position.
            positionOffset.x = homePosition.x;
        }
    }
}

void Nose::Draw() const
{
    Sprite::Draw();
}

void Nose::SetTransform(MyTransform parentTransform)
{
    transform = parentTransform;

    // Vector from the parent's rotation pivot to the nose.
    Vector2 noseFromPivot =
    {
        -parentTransform.pivot.x + positionOffset.x,
        -parentTransform.pivot.y + positionOffset.y
    };

    float radians = parentTransform.rotation * DEG2RAD;

    Vector2 rotatedPosition =
    {
        noseFromPivot.x * cosf(radians) -
        noseFromPivot.y * sinf(radians),

        noseFromPivot.x * sinf(radians) +
        noseFromPivot.y * cosf(radians)
    };

    // Position of the pivot in world space.
    Vector2 pivotPosition =
    {
        parentTransform.position.x +
            parentTransform.pivot.x,

        parentTransform.position.y +
            parentTransform.pivot.y
    };

    // Nose position = rotated vector from pivot.
    transform.position =
    {
        pivotPosition.x +
            rotatedPosition.x,

        pivotPosition.y +
            rotatedPosition.y
    };

    transform.rotation =
        parentTransform.rotation + localRotation;

    transform.pivot = { 0.0f, 0.0f };
}