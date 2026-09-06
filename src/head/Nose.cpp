//====================================================
// Nose.cpp
//
// Handles the robot's nose sprite and animation.
//
// The nose uses two levels of rotation:
//
// 1. Parent rotation:
//    The nose position rotates around the body/head
//    reference point, allowing it to follow the head
//    when the body/head rotates.
//
// 2. Local rotation:
//    The nose itself rotates around its own centre.
//
// This allows the nose to remain attached to the
// robot's head while also having independent movement.
//====================================================

#include "head/Nose.h"
#include "Constants.h"
#include <iostream>
#include <cmath>

//====================================================
// Initialise
//====================================================
//
// Loads the nose texture and sets up its animation.
//
// The nose uses the same anchor point supplied by the
// Head as the other head components.
//
// anchorOffset describes where the centre of the nose
// is located relative to the body/head reference point.
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

    rotation = 0.0f;
    scale = SCALE;

    // Position the nose relative to the body/head
    // reference point.
    //
    // X:
    // Position the nose horizontally using half of
    // the nose frame width.
    //
    // Y:
    // Position the nose around the vertical centre
    // of the head.
    //
    // anchorOffset is later rotated around anchorPoint
    // when the body/head rotates.
    anchorOffset =
    {
        FRAME_WIDTH / 2.0f,

        FRAME_HEIGHT / 2.0f
        - bodyHeight / 2.0f
        - headHeight / 2.0f
    };
}

//====================================================
// Update
//====================================================
//
// Updates the normal Sprite animation and applies the
// nose's independent local rotation.
//
// localRotation is separate from rotation.
//
// rotation:
//     Rotation inherited from the Head.
//
// localRotation:
//     Rotation belonging only to the nose.
//
//====================================================

void Nose::Update(float dt)
{
    // Update the base Sprite animation.
    Sprite::Update(dt);

    // Temporary continuous local rotation.
    //
    // This rotates the nose independently around its
    // own centre while it continues to follow the
    // head's movement and rotation.
    localRotation += 1.0f;
}

//====================================================
// Set Body / Head Dimensions
//====================================================
//
// Stores the body and head dimensions used to calculate
// the nose's position relative to the body/head anchor.
//
//====================================================

void Nose::SetBodyHeadDimensions(
    float bwidth,
    float bHeight,
    float hWidth,
    float hHeight
)
{
    bodyWidth = bwidth;
    bodyHeight = bHeight;

    headWidth = hWidth;
    headHeight = hHeight;
}

//====================================================
// Draw
//====================================================
//
// The nose uses two separate transforms:
//
// Parent transform:
//     anchorOffset is rotated around anchorPoint.
//
// Local transform:
//     the nose sprite is rotated around its own centre.
//
// This effectively creates:
//
//     Body/Head Pivot
//          ↓
//     rotate nose position
//          ↓
//     Nose Centre
//          ↓
//     rotate nose around itself
//
//====================================================

void Nose::Draw() const
{
    // Get the current animation frame.
    Rectangle source =
        animation.GetSourceRectangle();

    // Calculate the scaled dimensions of the nose.
    float width =
        animation.GetFrameWidth() * scale;

    float height =
        animation.GetFrameHeight() * scale;

    //================================================
    // Parent Transform
    //================================================
    //
    // anchorOffset represents the nose's position
    // relative to the body/head reference point.
    //
    // We rotate this offset around the parent's
    // anchorPoint so the nose follows the head's
    // rotation.
    //
    Vector2 offset = anchorOffset;

    // Raylib rotation values are in degrees while
    // sinf/cosf use radians.
    float radians =
        rotation * DEG2RAD;

    // Rotate the nose's position around the
    // body/head pivot.
    Vector2 rotatedOffset =
    {
        offset.x * cosf(radians)
            - offset.y * sinf(radians),

        offset.x * sinf(radians)
            + offset.y * cosf(radians)
    };

    //================================================
    // Nose World Position
    //================================================
    //
    // Add the rotated offset to the parent's
    // world-space anchor point.
    //
    // This gives us the centre of the nose after
    // the parent/head rotation has been applied.
    //
    Vector2 nosePosition =
    {
        anchorPoint.x
            + rotatedOffset.x * scale,

        anchorPoint.y
            + rotatedOffset.y * scale
    };

    //================================================
    // Nose Destination
    //================================================
    //
    // Build the destination rectangle around the
    // calculated centre of the nose.
    //
    // Subtracting half the width and height means
    // nosePosition represents the centre rather than
    // the top-left corner.
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
    // nosePosition, so its centre is simply half its
    // width and height.
    //
    // This is the nose's LOCAL rotation point.
    //
    // It is separate from anchorPoint, which remains
    // the body/head rotation reference point.
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
    // Adding them together means the nose inherits
    // the head rotation while also applying its own
    // local rotation.
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
