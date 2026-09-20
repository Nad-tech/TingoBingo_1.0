#include "body/Arms/Shoulder.h"
#include "Constants.h"
#include <cmath>
#include <iostream>
#include "raymath.h"

// Construct a shoulder using the shared body dimensions
// and the side of the body that the shoulder belongs to.
Shoulder::Shoulder(BodyDimensions& dimensions, std::string side)
    : dimensions(dimensions),
      side(side),
      upperArm(dimensions, side)
{
}

// Initialise the shoulder and its child upper arm.
void Shoulder::Initialise()
{
    // Texture loading is currently disabled because
    // the shoulder is being drawn as a rectangle while
    // the body articulation system is being developed.
    // texture = LoadTexture("assets/images/TingoBingo/body/Arm.png");

    // Sprite sheet layout.
    // The shoulder currently consists of a single frame.
    const int COLUMNS = 1;
    const int ROWS = 1;

    // Set the shoulder dimensions.
    // These values are stored in the shared BodyDimensions object
    // so other body parts can use the shoulder's dimensions when
    // calculating their own positions.
    dimensions.shoulderWidth = 75.0f;
    dimensions.shoulderHeight = 75.0f;

    // Calculate the total number of animation frames.
    const int TOTAL_FRAMES = COLUMNS * ROWS;

    // Default shoulder rotation.
    const float ROTATION = 0.0f;

    // Duration of each animation frame.
    const float FRAME_DURATION = 0.02f;

    // Initialise the shoulder animation using the shared dimensions.
    animation.Initialise
    (
        dimensions.shoulderWidth,
        dimensions.shoulderHeight,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    // Set the initial rotation and drawing scale.
    /*rotation = ROTATION;
    scale = SCALE;

    // Calculate the shoulder's local position relative to the body.
    //
    // The shoulder is positioned at the upper-left or upper-right
    // edge of the body depending on which side it belongs to.
    //
    // The X position places the centre of the shoulder just outside
    // the corresponding edge of the body.
    //
    // The Y position places the top of the shoulder at the top of
    // the body.
    if(side == "left")
    {
        anchorOffset = {
            (dimensions.bodyWidth / 2.0f) +
            (dimensions.shoulderWidth / 2.0f),

            -dimensions.bodyHeight / 2.0f
        }; 
    }
    else if(side == "right")
    {
        anchorOffset = {
            (-dimensions.bodyWidth / 2.0f) -
            (dimensions.shoulderWidth / 2.0f),

            -dimensions.bodyHeight / 2.0f
        }; 
    }

    // Initialise the upper arm.
    // The upper arm is a child of the shoulder and receives
    // the same shared BodyDimensions object.
    upperArm.Initialise();*/
}

// Update the shoulder and its child upper arm.
void Shoulder::Update(float dt)
{
    // Update the base Sprite state, including animation
    // and any rotation-related state.
    Sprite::Update(dt);

    // Start with the shoulder's local position relative to the body.
   /* Vector2 offset = anchorOffset;

    // Convert the shoulder's rotation from degrees to radians
    // for use with the trigonometric functions.
    float radians = rotation * DEG2RAD;

    // Rotate the local offset around the body's anchor point.
    //
    // This allows the shoulder to maintain its correct position
    // relative to the body when the body or shoulder is rotated.
    Vector2 rotatedOffset =
    {
        (offset.x * cosf(radians) -
         offset.y * sinf(radians)) * scale,

        (offset.x * sinf(radians) +
         offset.y * cosf(radians)) * scale
    };

    // Convert the rotated local position into a world-space position.
    //
    // armAnchorPosition represents the shoulder's actual position
    // in the world and is used as the anchor point for the upper arm.
    armAnchorPosition =
    {
        anchorPoint.x + rotatedOffset.x,
        anchorPoint.y + rotatedOffset.y
    };

    // Pass the shoulder's world-space position to the upper arm.
    //
    // This establishes the parent-child relationship:
    //
    // Body -> Shoulder -> UpperArm
    //
    // The upper arm can now position itself relative to the shoulder
    // instead of calculating its position directly from the body.
    upperArm.SetAnchorPoint(armAnchorPosition);

    // Update the child upper arm.
    upperArm.Update(dt);*/
}

// Return the current shoulder animation frame.
int Shoulder::GetFrame() const
{
    return animation.GetFrame();
}

// Set the shoulder rotation and pass the rotation
// down to the child upper arm.
void Shoulder::SetRotation(float rotation)
{
    //Sprite::SetRotation(rotation);

    // Keep the upper arm aligned with the shoulder's rotation.
   // upperArm.SetRotation(rotation);
}

// Draw the shoulder and its child upper arm.
void Shoulder::Draw() const
{
    // Define the shoulder's destination rectangle.
    //
    // armAnchorPosition represents the top-centre of the shoulder
    // because the drawing origin is positioned at the top-centre below.
    /*Rectangle shoulder =
    {
        armAnchorPosition.x,
        armAnchorPosition.y,
        dimensions.shoulderWidth * scale,
        dimensions.shoulderHeight * scale
    };
    
    // Set the drawing origin to the top-centre of the shoulder.
    //
    // This makes the shoulder rotate around its attachment point
    // rather than around its centre.
    Vector2 origin =
    {
        dimensions.shoulderWidth * scale / 2.0f,
        0
    };

    // Draw the upper arm first so that the shoulder is rendered
    // over the top of it.
    upperArm.Draw();

    // Draw the shoulder on top of the upper arm.
    DrawRectanglePro(
        shoulder,
        origin,
        rotation,
        BROWN
    );*/
}

// Set the body's anchor point used by the shoulder.
//
// The shoulder uses this point as the parent position from which
// its local offset is calculated.
void Shoulder::SetAnchorPoint(Vector2 anchorPoint)
{
    //this->anchorPoint = anchorPoint;
}

// Start or control the upper arm's swinging movement.
void Shoulder::SwingArm(
    float dt,
    float swingMinAngle,
    float swingMaxAngle
)
{
    upperArm.SwingArm(dt, swingMinAngle, swingMaxAngle);
}