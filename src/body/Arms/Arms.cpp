#include "body/Arms/Arms.h"

void Arms::Initialise()
{
    leftUpperArm.Initialise();
    rightUpperArm.Initialise();
}

void Arms::SetBodyDimensions(float bodyWidth, float bodyHeight)
{
    leftUpperArm.SetBodyDimensions(bodyWidth, bodyHeight, "left");
    rightUpperArm.SetBodyDimensions(bodyWidth, bodyHeight, "right");
}

void Arms::Shutdown()
{
    leftUpperArm.Shutdown();
    rightUpperArm.Shutdown();
}

void Arms::Update(float dt)
{
    leftUpperArm.Update(dt);
    rightUpperArm.Update(dt);

    if(swingLeftUpperArm)
    {
        leftUpperArm.SwingArm(dt, 0, 180);
    }

    if(swingRightUpperArm)
    {
        rightUpperArm.SwingArm(dt, 100, 180);
    }
}

void Arms::Draw() const 
{
    leftUpperArm.Draw();
    rightUpperArm.Draw();
}

void Arms::SetAnchorPoint(Vector2 anchorPoint)
{
    leftUpperArm.SetAnchorPoint(anchorPoint);
    rightUpperArm.SetAnchorPoint(anchorPoint);
}

void Arms::SetRotation(float rotation) 
{
    leftUpperArm.SetRotation(rotation);
    rightUpperArm.SetRotation(rotation);
}

void Arms::SwingArm(std::string side, bool swing)
{
    if(side == "left" && swing)
    {
        swingLeftUpperArm = true;
    }
    else if(side == "left" && !swing)
    {
        swingLeftUpperArm = false;
    }

    if(side == "right" && swing)
    {
        swingRightUpperArm = true;
    }
    else if(side == "right" && !swing)
    {
        swingRightUpperArm = false;
    }
}