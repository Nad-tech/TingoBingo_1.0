#include "body/Arms/Shoulder.h"
#include "Constants.h"
#include <cmath>
#include <iostream>
#include "raymath.h"

// Construct a shoulder using the shared body dimensions
// and the side of the body that the shoulder belongs to.
Shoulder::Shoulder(BodyDimensions& dimensions, std::string side) :
    Shape(CARDBOARD_DARK),
    dimensions(dimensions),
    side(side),
    upperArm(dimensions, side)
{
}

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
    upperArm.Update(dt);
}

void Shoulder::Draw() const 
{
    Shape::Draw();
    upperArm.Draw();
}

void Shoulder::SetTransform(MyTransform parentTransform)
{
    Shape::transform.position = {
        parentTransform.position.x + positionOffset.x,
        parentTransform.position.y + positionOffset.y
    };

    Shape::transform.pivot = {
        -positionOffset.x,
        -positionOffset.y
    };

    Shape::transform.rotation = parentTransform.rotation;
    Shape::transform.scale = parentTransform.scale;

    upperArm.SetTransform(Shape::transform);
}

void Shoulder::SwingArm(
    float dt,
    float swingMinAngle,
    float swingMaxAngle
)
{
    upperArm.SwingArm(dt, swingMinAngle, swingMaxAngle);
}