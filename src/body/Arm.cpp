#include "body/Arm.h"
#include "Constants.h"
#include <cmath>
#include <iostream>

// Load the arm sprite and initialise its animation.
void Arm::Initialise()
{
    texture = LoadTexture("assets/images/TingoBingo/body/Arm.png");

    // Sprite sheet layout.
    const int COLUMNS = 1;
    const int ROWS = 1;

    // Calculate the size of a single animation frame.
    const int FRAME_WIDTH = texture.width / COLUMNS;
    const int FRAME_HEIGHT = texture.height / ROWS;

    const int TOTAL_FRAMES = COLUMNS * ROWS;

    // Animation settings.
    const float ROTATION = 0.0f;
    const float FRAME_DURATION = 0.02f;

    // Initialise the animation using the sprite sheet information.
    animation.Initialise
    (
        FRAME_WIDTH,
        FRAME_HEIGHT,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    rotation = ROTATION;
    scale = SCALE;

    // Position the arm's anchor point relative to the body.
    // The anchor point represents where the arm attaches
    // to the body at the shoulder.
    if(side == "left")
    {
        localPositionOffset = {
            bodyWidth / 2 + FRAME_WIDTH,
            -bodyHeight / 2
        }; 
    }
    else if(side == "right")
    {
        localPositionOffset = {
            -bodyWidth / 2.0f,
            -bodyHeight / 2.0f
        }; 
    }

    homeRotation = rotation;
}

void Arm::Update(float dt)
{
    Sprite::Update(dt);
}

// Return the current arm animation frame.
int Arm::GetFrame() const
{
    return animation.GetFrame();
}

// Apply a rotation to the arm.
void Arm::SetRotation(float rotation)
{
    Sprite::SetRotation(rotation);
}

// Set the dimensions of the body so the arm can be positioned
// correctly relative to the body.
void Arm::SetBodyDimensions(float width, float height, std::string side)
{
    bodyWidth = width;
    bodyHeight = height;
    this->side = side; 
}

void Arm::Draw() const
{
    // Get the current animation frame.
    Rectangle source = animation.GetSourceRectangle();

    // Calculate the scaled dimensions of the arm.
    float width = animation.GetFrameWidth() * scale;
    float height = animation.GetFrameHeight() * scale;

    //================================================
    // Parent Transform
    //================================================
    //
    // localPositionOffset represents the arm's local
    // position relative to the body anchor point.
    //
    // Rotate this local offset around the body anchor
    // so the arm follows the body's rotation.
    //
    Vector2 offset = localPositionOffset;

    // Raylib rotation values are measured in degrees,
    // while sinf() and cosf() require radians.
    float radians = rotation * DEG2RAD;

    // Rotate the arm's local offset around the
    // body anchor point.
    Vector2 rotatedOffset =
    {
        offset.x * cosf(radians) - offset.y * sinf(radians),
        offset.x * sinf(radians) + offset.y * cosf(radians)
    };

    //================================================
    // Arm World Position
    //================================================
    //
    // Add the rotated local offset to the body's
    // world-space anchor point.
    //
    // The arm anchor point is attached to the body
    // at the shoulder and follows the body's rotation.
    //
    Vector2 armAnchorPosition =
    {
        anchorPoint.x + rotatedOffset.x * scale,
        anchorPoint.y + rotatedOffset.y * scale
    };

    //================================================
    // Arm Destination
    //================================================
    //
    // Position the arm sprite using its anchor point.
    //
    // The anchor point is at the top-centre of the
    // arm sprite, where the arm attaches to the shoulder.
    //
    Rectangle destination =
    {
        armAnchorPosition.x - width / 2.0f,
        armAnchorPosition.y,
        width,
        height
    };

    //================================================
    // Local Rotation Pivot
    //================================================
    //
    // Set the rotation origin to the top-centre of the arm.
    //
    // This is the point where the arm attaches to the
    // body at the shoulder, allowing the arm to rotate
    // around the shoulder rather than its centre.
    //
    Vector2 origin =
    {
        width / 2.0f,
        0
    };

    //================================================
    // Draw
    //================================================
    //
    // rotation:
    //     Rotation inherited from the body.
    //
    // localRotation:
    //     Independent rotation of the arm.
    //
    // Adding the two rotations allows the arm to
    // follow the body while also rotating independently.
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

void Arm::SwingArm(float dt, float swingMinAngle, float swingMaxAngle)
{
    swingTime += dt * SWING_SPEED;

    if (swingTime >= 2.0f * PI)
    {
        swingTime -= 2.0f * PI;
    }

    float unitAngle = 0;
    
    if(side == "left")
    {
        unitAngle = -(sinf(swingTime) + 1.0f) / 2.0f;
    }

    if(side == "right")
    {
        unitAngle = (sinf(swingTime) + 1.0f) / 2.0f;
    }

    localRotation =
            swingMinAngle +
            unitAngle * (swingMaxAngle - swingMinAngle);
}
