#include "head/Head.h"

void Head::Initialise()
{
    headBase.Initialise();
    antenna.Initialise();
    ears.Initialise();
    eyeBrows.Initialise();
    eyes.Initialise();
    mouth.Initialise();
    nose.Initialise();
}

void Head::Shutdown()
{
    headBase.Shutdown();
    antenna.Shutdown();
    ears.Shutdown();
    eyeBrows.Shutdown();
    eyes.Shutdown();
    mouth.Shutdown();
    nose.Shutdown();
}

void Head::Update(float dt)
{
    headBase.Update(dt);
    antenna.Update(dt);
    ears.Update(dt);
    eyeBrows.Update(dt);
    eyes.Update(dt);
    mouth.Update(dt);
    nose.Update(dt);
}

void Head::Draw() const
{
    
    antenna.Draw();
   
    if (IsFrontFacing())
    {
        ears.Draw();
        headBase.Draw();
        eyes.Draw();
        mouth.Draw();
        nose.Draw();
        eyeBrows.Draw();
        antenna.Draw();
    }
    else {
        headBase.Draw();
    }
    
}

void Head::SetPosition(Vector2 position) 
{
    this->position = position;
    
    headBase.SetPosition(position);
    antenna.SetPosition(position);
    ears.SetPosition(position);
    eyeBrows.SetPosition(position);
    eyes.SetPosition(position);
    mouth.SetPosition(position);
    nose.SetPosition(position);
}

Vector2 Head::GetPosition() const
{
    return position;
}

void Head::RotateLeft()
{
    headBase.RotateLeft();
}

void Head::RotateRight()
{
    headBase.RotateRight();
}

void Head::ReturnToCentre()
{
    headBase.ReturnToCentre();
}

bool Head::IsFrontFacing() const
{
    return headBase.GetFrame() == 0;
}