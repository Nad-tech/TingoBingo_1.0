#include "body/Legs/Legs.h"

void Legs::Initialise()
{
    leftThigh.Initialise();
    rightThigh.Initialise();
}

void Legs::Shutdown()
{
    leftThigh.Shutdown();
    rightThigh.Shutdown();
}

void Legs::Update(float dt)
{
    leftThigh.Update(dt);
    rightThigh.Update(dt);
}

void Legs::Draw() const
{
    leftThigh.Draw();
    rightThigh.Draw();
}

void Legs::SetAnchorPoint(Vector2 anchorPoint)
{
    leftThigh.SetAnchorPoint({anchorPoint.x, anchorPoint.y});
    rightThigh.SetAnchorPoint({anchorPoint.x, anchorPoint.y}); 
}

void Legs::SetRotation(float rotation)
{
    leftThigh.SetRotation(rotation);
    rightThigh.SetRotation(rotation);
}

void Legs::SetBodyDimension(float bodyWidth, float bodyHeight)
{
    leftThigh.SetBodyDimensions(
        bodyWidth,
        bodyHeight,
        "left"
    );

    rightThigh.SetBodyDimensions(
        bodyWidth,
        bodyHeight,
        "right"
    );
}