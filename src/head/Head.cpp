#include "head/Head.h"
#include<cmath>

Head::Head() :
    rotation(0.0f),
    scale(0.0f),

    homeRotation(rotation),
    headWiggleTimer(0.0f),
    headWiggleAmplitude(0.0f),
    headWiggling(false),
    nextHeadWiggle((float)GetRandomValue(5, 7)),
    headWiggleFrequency(0.0f),

    headBobOffset({0.0f, 0.0f}),
    headBobScale(7.0f),
    headBobAngle(0.0f),
    headBobDirection(1.0f),
    randomHeadBobSignTimer((float)GetRandomValue(5, 10)),
    headBobRadiusX(GetRandomValue(3, 8)),
    headBobRadiusY(GetRandomValue(2, 6)),
    headBobSpeed(GetRandomValue(6, 14) / 10.0f)
{
}

void Head::Initialise()
{
    headBase.Initialise();
    antenna.Initialise();
    ears.Initialise();
    eyebrows.Initialise();
    eyes.Initialise();
    mouth.Initialise();
    nose.Initialise();
    pupils.Initialise();
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
    pupils.Shutdown();
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
    pupils.Update(dt);
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
        pupils.Draw();
    }
    else {
        headBase.Draw();
    }
    
}

void Head::SetPosition(Vector2 position) 
{
    this->homePosition = position;
    ApplyPosition(position);
}

void Head::ApplyPosition(Vector2 position)
{
    this->position = position;

    headBase.SetPosition(position);
    antenna.SetPosition(position);
    ears.SetPosition(position);
    eyebrows.SetPosition(position);
    eyes.SetPosition(position);
    mouth.SetPosition(position);
    nose.SetPosition(position);
    pupils.SetPosition(position);
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

void Head::SetRotation(float rotation)
{
    homeRotation = rotation;
    ApplyRotation(rotation); 
}

void Head::ApplyRotation(float rotation)
{
    this->rotation = rotation;

    headBase.SetRotation(rotation);
    antenna.SetRotation(rotation);
    ears.SetRotation(rotation);
    eyebrows.SetRotation(rotation);
    eyes.SetRotation(rotation);
    mouth.SetRotation(rotation);
    nose.SetRotation(rotation);
    pupils.SetRotation(rotation);
}

void Head::PlayIdleHeadTransform(float dt)
{
    PlayHeadBob(dt);
    ApplyPosition(position);

    PlayHeadWiggle(dt);
    ApplyRotation(rotation);
}

void Head::PlayHeadWiggle(float dt)
{
    nextHeadWiggle -= dt;

    if (nextHeadWiggle <= 0.0f && !headWiggling)
    {
        headWiggling = true;
        headWiggleTimer = 0.0f;
        headWiggleAmplitude = (float)GetRandomValue(10, 20);
        nextHeadWiggle = (float)GetRandomValue(5, 7);
        headWiggleFrequency = (float)GetRandomValue(10, 40);
    }

    if (headWiggling)
    {
        headWiggleTimer += dt;

        rotation = sin(headWiggleTimer * headWiggleFrequency) * headWiggleAmplitude;

        headWiggleAmplitude -= 8.0f * dt;

        if (headWiggleAmplitude <= 0.0f)
        {
            headWiggling = false;
            rotation = homeRotation;
        }
    }
}

void Head::PlayHeadBob(float dt)
{
    headBobAngle += dt * headBobSpeed * headBobDirection;

    randomHeadBobSignTimer -= dt;

    if(randomHeadBobSignTimer <= 0)
    {
        headBobDirection *= -1;
        randomHeadBobSignTimer = (float)GetRandomValue(5,10);
        headBobRadiusX = GetRandomValue(3, 8);
        headBobRadiusY = GetRandomValue(2, 6);
        headBobSpeed = GetRandomValue(6, 14) / 10.0f;
    }

    headBobOffset.x = cos(headBobAngle) * headBobRadiusX;
    headBobOffset.y = sin(headBobAngle) * headBobRadiusY;

    position.x = homePosition.x + headBobOffset.x;
    position.y = homePosition.y + headBobOffset.y; 
}

void Head::LookAt(Vector2 point)
{
    pupils.LookAt(point);
}
