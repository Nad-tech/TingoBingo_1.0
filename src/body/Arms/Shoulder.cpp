#include "body/Arms/Shoulder.h"
#include "Constants.h"
#include <cmath>
#include <iostream>

// Load the shoulder sprite and initialise its animation.
void Shoulder::Initialise()
{
    //texture = LoadTexture("assets/images/TingoBingo/body/Arm.png");

    // Sprite sheet layout.
    const int COLUMNS = 1;
    const int ROWS = 1;

    // Calculate the size of a single animation frame.
    const int FRAME_WIDTH = 100;//texture.width / COLUMNS;
    const int FRAME_HEIGHT = 100;//texture.height / ROWS;

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

    // Position the shoulder's anchor point relative to the body.
    // The anchor point represents where the shoulder attaches
    // to the body.
    if(side == "left")
    {
        localPositionOffset = {
            (bodyWidth / 2.0f) + SHOULDER_WIDTH / 2.0f,
            -bodyHeight / 2.0f

        }; 
    }
    else if(side == "right")
    {
        localPositionOffset = {
            (-bodyWidth / 2.0f) - SHOULDER_WIDTH / 2.0f,
            -bodyHeight / 2.0f
        }; 
    }

    homeRotation = rotation;
}

void Shoulder::Update(float dt)
{
    Sprite::Update(dt);
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
}

// Set the dimensions of the body so the shoulder can be positioned
// correctly relative to the body.
void Shoulder::SetBodyDimensions(float width, float height, std::string side)
{
    bodyWidth = width;
    bodyHeight = height;
    this->side = side; 
}

void Shoulder::Draw() const
{
    Vector2 offset = localPositionOffset;

    float radians = rotation * DEG2RAD;

    Vector2 rotatedOffset =
    {
        (offset.x * cosf(radians) - offset.y * sinf(radians))*scale,
        (offset.x * sinf(radians) + offset.y * cosf(radians))*scale
    };

    Vector2 armAnchorPosition =
    {
        anchorPoint.x + rotatedOffset.x,
        anchorPoint.y + rotatedOffset.y
    };

    Rectangle shoulder =
    {
        armAnchorPosition.x,
        armAnchorPosition.y,
        SHOULDER_WIDTH * scale,
        SHOULDER_HEIGHT * scale
    };
    
    Vector2 origin =
        {
            SHOULDER_WIDTH * scale / 2.0f,
            0
        };

    DrawRectanglePro(
        shoulder,
        origin,
        rotation + localRotation,
        BROWN
    );
}

void Shoulder::SwingArm(float dt, float swingMinAngle, float swingMaxAngle)
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
