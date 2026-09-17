#include "body/Arms/Shoulder.h"
#include "Constants.h"
#include <cmath>
#include <iostream>
#include "raymath.h"

Shoulder::Shoulder(BodyDimensions& dimensions, std::string side)
    : dimensions(dimensions),
      side(side),
      upperArm(dimensions, side)
{
}

// Load the shoulder sprite and initialise its animation.
void Shoulder::Initialise()
{
    //texture = LoadTexture("assets/images/TingoBingo/body/Arm.png");

    // Sprite sheet layout.
    const int COLUMNS = 1;
    const int ROWS = 1;

    // Calculate the size of a single animation frame.
    // Keep the shoulder dimensions aligned with the original sprite size
    // so the shared BodyDimensions values still produce the correct scale.
    dimensions.shoulderWidth = 75.0f;//texture.width / COLUMNS;
    dimensions.shoulderHeight = 75.0f;//texture.height / ROWS;

    const int TOTAL_FRAMES = COLUMNS * ROWS;

    // Animation settings.
    const float ROTATION = 0.0f;
    const float FRAME_DURATION = 0.02f;

    // Initialise the animation using the sprite sheet information.
    animation.Initialise
    (
        dimensions.shoulderWidth,
        dimensions.shoulderHeight,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    rotation = ROTATION;
    scale = SCALE;

    // Position the shoulder's anchor point relative to the body.
    // The anchor point represents where the shoulder attaches
    // to the body.
    if(side == "left")
    {
        localPositionOffset = {
            (dimensions.bodyWidth / 2.0f) + (dimensions.shoulderWidth / 2.0f),
            -dimensions.bodyHeight / 2.0f
        }; 
    }
    else if(side == "right")
    {
        localPositionOffset = {
            (-dimensions.bodyWidth / 2.0f) - (dimensions.shoulderWidth / 2.0f),
            -dimensions.bodyHeight / 2.0f
        }; 
    }

    upperArm.Initialise();
}

void Shoulder::Update(float dt)
{
    Sprite::Update(dt);
   
    Vector2 offset = localPositionOffset;

    float radians = rotation * DEG2RAD;

    Vector2 rotatedOffset =
    {
        (offset.x * cosf(radians) - offset.y * sinf(radians))*scale,
        (offset.x * sinf(radians) + offset.y * cosf(radians))*scale
    };

    armAnchorPosition =
    {
        anchorPoint.x + rotatedOffset.x,
        anchorPoint.y + rotatedOffset.y
    };

    upperArm.SetAnchorPoint(armAnchorPosition);
    upperArm.Update(dt);
}

// Return the current shoulder animation frame.
int Shoulder::GetFrame() const
{
    return animation.GetFrame();
}

// Apply a rotation to the shoulder.
void Shoulder::SetRotation(float rotation)
{
    Sprite::SetRotation(rotation);
    upperArm.SetRotation(rotation);
}

void Shoulder::Draw() const
{
    Rectangle shoulder =
    {
        armAnchorPosition.x,
        armAnchorPosition.y,
        dimensions.shoulderWidth * scale,
        dimensions.shoulderHeight * scale
    };
    
    Vector2 origin =
        {
            dimensions.shoulderWidth * scale / 2.0f,
            0
        };

    upperArm.Draw();

    DrawRectanglePro(
        shoulder,
        origin,
        rotation,
        BROWN
    );
}

void Shoulder::SetAnchorPoint(Vector2 anchorPoint)
{
    this->anchorPoint = anchorPoint;
}

void Shoulder::SwingArm(float dt, float swingMinAngle, float swingMaxAngle)
{
    upperArm.SwingArm(dt, swingMinAngle, swingMaxAngle);
}