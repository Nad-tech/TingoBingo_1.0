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
    dimensions.shoulderWidth = 75.0f;
    dimensions.shoulderHeight = 75.0f;
    SetDimensions(dimensions.shoulderWidth, dimensions.shoulderHeight);

    upperArm.Initialise();

    if(side == "left") 
    {
        positionOffset = {
            dimensions.bodyWidth / 2.0f + dimensions.shoulderWidth / 2.0f,
            dimensions.bodyHeight / 2.0f - dimensions.shoulderHeight / 2.0f
        };
    }

    if(side == "right") 
    {
        positionOffset = {
            -dimensions.bodyWidth / 2.0f - dimensions.shoulderWidth / 2.0f,
            dimensions.bodyHeight / 2.0f - dimensions.shoulderHeight / 2.0f
        };
    }
}

// Update the shoulder and its child upper arm.
void Shoulder::Update(float dt)
{
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

void Shoulder::Draw() const 
{
    upperArm.Draw();
    Shape::Draw();
}
// Set the body's anchor point used by the shoulder.
//
// The shoulder uses this point as the parent position from which
// its local offset is calculated.
void Shoulder::SetTransform(MyTransform parentTransform)
{
    transform.position = {
        parentTransform.position.x + positionOffset.x,
        parentTransform.position.y + positionOffset.y
    };

    transform.pivot = 
    {
        -positionOffset.x,
        -positionOffset.y
    };
    transform.rotation = parentTransform.rotation;
    transform.scale = parentTransform.scale;

    Shape::transform = transform;
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