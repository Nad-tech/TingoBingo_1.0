#include "body/Arms/Arms.h"

Arms::Arms(BodyDimensions& dimensions)
    : dimensions(dimensions),
      leftShoulder(dimensions, "left"),
      rightShoulder(dimensions, "right")
{
}

void Arms::Initialise()
{
    leftShoulder.Initialise();
    rightShoulder.Initialise();
}

void Arms::Shutdown()
{
    leftShoulder.Shutdown();
    rightShoulder.Shutdown();
}

void Arms::Update(float dt)
{
    leftShoulder.Update(dt);
    rightShoulder.Update(dt);

    if(swingLeftArm)
    {
        leftShoulder.SwingArm(dt, 0, 180);
    }

    if(swingRightArm)
    {
        rightShoulder.SwingArm(dt, 0, 180);
    }
}

void Arms::Draw() const 
{
    leftShoulder.Draw();
    rightShoulder.Draw();
}

void Arms::SetAnchorPoint(Vector2 anchorPoint)
{
    leftShoulder.SetAnchorPoint(anchorPoint);
    rightShoulder.SetAnchorPoint(anchorPoint);
}

void Arms::SetRotation(float rotation) 
{
    leftShoulder.SetRotation(rotation);
    rightShoulder.SetRotation(rotation);
}

void Arms::SwingArm(std::string side, bool swing)
{
    if(side == "left" && swing)
    {
        swingLeftArm = true;
    }
    else if(side == "left" && !swing)
    {
        swingLeftArm = false;
    }

    if(side == "right" && swing)
    {
        swingRightArm = true;
    }
    else if(side == "right" && !swing)
    {
        swingRightArm = false;
    }
}