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

#include "head/Nose.h"
#include "Constants.h"
#include <iostream>
#include <cmath>

Vector2 Vector2Add(Vector2 a, Vector2 b)
{
    return {a.x + b.x , a.y + b.y};
}

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
    std::cout << "NOSE INITIALISE\n";

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
    const int FRAME_WIDTH =
        texture.width / COLUMNS;

    const int FRAME_HEIGHT =
        texture.height / ROWS;

    const int TOTAL_FRAMES =
        COLUMNS * ROWS;

    // Time between animation frames.
    const float FRAME_DURATION = 0.08f;

    // Initialise the animation system.
    animation.Initialise(
        FRAME_WIDTH,
        FRAME_HEIGHT,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    //================================================
    // Sprite Transform
    //================================================

    // The nose initially has no local rotation.
    rotation = 0.0f;

    // Use the global robot sprite scale.
    scale = SCALE;

    //================================================
    // Nose Position
    //================================================
    //
    // localPositionOffset is expressed in LOCAL coordinates
    // relative to anchorPoint.
    //
    // X:
    // Position the nose horizontally relative to the
    // parent anchor using half of the nose frame width.
    //
    // Y:
    // Position the nose vertically using the nose frame
    // height and the stored body/head dimensions.
    //
    // The offset is rotated around anchorPoint in Draw()
    // when the head rotates.
    //
    //================================================

    localPositionOffset =
    {
        FRAME_WIDTH / 2.0f,

        FRAME_HEIGHT / 2.0f
        - bodyHeight / 2.0f
        - headHeight / 2.0f
    };

    // Store the original LOCAL offset.
    //
    // This is deliberately not a world-space position.
    // The wiggle animation uses this as the nose's
    // permanent home position.
    homeAnchorPoint = localPositionOffset;
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

        // The original local anchor position is already
        // stored in homeAnchorPoint.
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
        localPositionOffset.x =
            homeAnchorPoint.x + wiggleOffSetX;

        // The wiggle lasts for one second.
        if (noseWiggleTimer >= 1.0f)
        {
            // Stop the wiggle.
            noseWiggling = false;

            // Reset the wiggle state.
            noseWiggleTimer = 0.0f;
            wiggleOffSetX = 0.0f;

            // Restore the original LOCAL anchor position.
            localPositionOffset.x = homeAnchorPoint.x;
        }
    }
}

//====================================================
// Set Body / Head Dimensions
//====================================================
//
// Stores the body and head dimensions used when
// calculating the nose's position relative to the
// body/head anchor point.
//
// These values are used by Initialise() to calculate
// localPositionOffset.
//
//====================================================

void Nose::SetBodyHeadDimensions(
    float bwidth,
    float bHeight,
    float hWidth,
    float hHeight
)
{
    // Store the supplied body dimensions.
    bodyWidth = bwidth;
    bodyHeight = bHeight;

    // Store the supplied head dimensions.
    headWidth = hWidth;
    headHeight = hHeight;
}

//====================================================
// Draw
//====================================================
//
// The nose uses two separate transforms.
//
// Parent transform:
//     Rotates the nose's POSITION around anchorPoint.
//
// Local transform:
//     Rotates the nose SPRITE around its own centre.
//
// This creates the following transform hierarchy:
//
//     Body / Head Pivot
//            |
//            v
//     Rotate nose position
//            |
//            v
//       Nose Centre
//            |
//            v
//     Rotate nose sprite
//
// The parent rotation controls where the nose is
// positioned around the head.
//
// The local rotation controls the nose's own rotation.
//
//====================================================

void Nose::Draw() const
{
    // Get the current animation frame.
    Rectangle source = animation.GetSourceRectangle();

    // Calculate the scaled dimensions of the nose.
    float width = animation.GetFrameWidth() * scale;

    float height = animation.GetFrameHeight() * scale;

    //================================================
    // Parent Transform
    //================================================
    //
    // localPositionOffset represents the nose's LOCAL position
    // relative to the body/head anchor point.
    //
    // Rotate this local offset around the parent anchor
    // so the nose follows the head when it rotates.
    //
    Vector2 offset = localPositionOffset;

    // Raylib rotation values are measured in degrees,
    // while sinf() and cosf() require radians.
    float radians = rotation * DEG2RAD;

    // Rotate the nose's local position around the
    // body/head pivot.
    Vector2 rotatedOffset =
    {
        offset.x * cosf(radians) - offset.y * sinf(radians),
        offset.x * sinf(radians) + offset.y * cosf(radians)
    };

    //================================================
    // Nose World Position
    //================================================
    //
    // Add the rotated local offset to the parent's
    // world-space anchor point.
    //
    // The result is the nose's world-space centre
    // after the parent/head rotation has been applied.
    //
    Vector2 nosePosition =
    {
        anchorPoint.x + rotatedOffset.x * scale,
        anchorPoint.y + rotatedOffset.y * scale
    };

    //================================================
    // Nose Destination
    //================================================
    //
    // Build the destination rectangle around the
    // calculated nose centre.
    //
    // Subtracting half the width and height means
    // nosePosition represents the centre of the sprite
    // rather than its top-left corner.
    //
    Rectangle destination =
    {
        nosePosition.x - width / 2.0f,
        nosePosition.y - height / 2.0f,
        width,
        height
    };

    //================================================
    // Local Rotation Pivot
    //================================================
    //
    // The destination rectangle is centred around
    // nosePosition.
    //
    // Therefore, the centre of the rectangle is simply
    // half its width and half its height.
    //
    // This is the nose's LOCAL rotation origin.
    //
    // It is separate from anchorPoint, which remains
    // the parent/body/head rotation reference point.
    //
    Vector2 origin =
    {
        width / 2.0f,
        height / 2.0f
    };

    //================================================
    // Draw
    //================================================
    //
    // rotation:
    //     Parent/head rotation.
    //
    // localRotation:
    //     Independent nose rotation.
    //
    // Adding the two rotations causes the nose to
    // inherit the head's rotation while also applying
    // its own independent local rotation.
    //
    DrawTexturePro(
        texture,
        source,
        destination,
        origin,
        rotation + localRotation,
        WHITE
    );
}
