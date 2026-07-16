#include "head/Head.h"
#include "head/Antenna.h"

void Head::Initialise()
{
    headBase.Initialise();
    antenna.Initialise();
    ears.Initialise();
    eyeBrows.Initialise();
    eyes.Initialise();
    mouth.Initialise();
}

void Head::Shutdown()
{
    headBase.Shutdown();
    antenna.Shutdown();
    ears.Shutdown();
    eyeBrows.Shutdown();
    eyes.Shutdown();
    mouth.Shutdown();
}

void Head::Update(float dt)
{
    headBase.Update();
    antenna.Update();
    ears.Update();
    eyeBrows.Update();
    eyes.Update();
    mouth.Update();
}

void Head::Draw() const
{
    headBase.Draw();
    antenna.Draw();
    ears.Draw();
    eyeBrows.Draw();
    eyes.Draw();
    mouth.Draw();
}

void Head::SetPosition(Vector2 position) 
{
    headBase.SetPosition(position);
    antenna.SetPosition(position);
    ears.SetPosition(position);
    eyeBrows.SetPosition(position);
    eyes.SetPosition(position);
    mouth.SetPosition(position);
}
