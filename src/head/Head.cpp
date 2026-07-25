#include "head/Head.h"

void Head::Initialise()
{
    headBase.Initialise();
    antenna.Initialise();
    ears.Initialise();
    eyebrows.Initialise();
    eyes.Initialise();
    mouth.Initialise();
    nose.Initialise();
}

void Head::Shutdown()
{
    headBase.Shutdown();
    antenna.Shutdown();
    ears.Shutdown();
    eyebrows.Shutdown();
    eyes.Shutdown();
    mouth.Shutdown();
    nose.Shutdown();
}

void Head::Update(float dt)
{
    headBase.Update(dt);
    antenna.Update(dt);
    ears.Update(dt);
    eyebrows.Update(dt);
    eyes.Update(dt);
    mouth.Update(dt);
    nose.Update(dt);
}

void Head::Draw() const
{   
    if (IsFrontFacing())
    {
        ears.Draw();
        headBase.Draw();
        eyes.Draw();
        mouth.Draw();
        nose.Draw();
        eyebrows.Draw();
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
    eyebrows.SetPosition(position);
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

void Head::PlayIdleAntennaAnimation() 
{
    antenna.PlayWiggle();
}

void Head::PlayIdleEarsAnimation() 
{
    ears.PlayWiggle();
}

void Head::PlayIdleEyebrowsAnimation()
{
    eyebrows.PlayWiggle();
}

void Head::PlayIdleEyesAnimation()
{
    eyes.PlayBlink();
}

void Head::PlayIdleMouthAnimation()
{
    mouth.PlayIdleMouth();
}

void Head::PlayIdleNoseAnimation()
{
    nose.PlayWiggle();
}