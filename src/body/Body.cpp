#include "body/Body.h"
#include <cmath>
#include "Emotion.h"

Body::Body(BodyDimensions& dimensions) :
    dimensions(dimensions),
    transform(),
    homeTransform(), 
    bodyBase(dimensions),
    neck(dimensions),
    pelvis(dimensions),
    arms(dimensions),
    bodyWiggleTimer(0.0f),
    bodyWiggleAmplitude(0.0f),
    bodyWiggling(false),
    nextBodyWiggle((float)GetRandomValue(5, 7)),
    bodyWiggleFrequency(0.0f),
    bodyBobOffset({0.0f, 0.0f}),
    bodyBobScale(7.0f),
    bodyBobAngle(0.0f),
    bodyBobDirection(1.0f),
    randomBodyBobSignTimer((float)GetRandomValue(5, 10)),
    bodyBobRadiusX(GetRandomValue(3, 8)),
    bodyBobRadiusY(GetRandomValue(2, 6)),
    bodyBobSpeed(GetRandomValue(6, 14) / 10.0f)
{}

void Body::Initialise()
{
    homeTransform = transform;
    bodyBase.Initialise();
    neck.Initialise();
    arms.Initialise();
    pelvis.Initialise();
}

void Body::Shutdown()
{
    neck.Shutdown();
    bodyBase.Shutdown();
    arms.Shutdown();
    pelvis.Shutdown();
}

void Body::Update(float dt, bool speaking, Emotion emotion)
{
    neck.Update(dt, speaking, emotion);
    bodyBase.Update(dt);
    arms.Update(dt);
    pelvis.Update(dt);
    
    PlayIdleBodyTransform(dt);
}

void Body::Draw() const
{
    
    bodyBase.Draw();
    arms.Draw();
    neck.Draw();
    pelvis.Draw();
}

void Body::SetTransform(MyTransform transform)
{
    this->transform = transform;
    bodyBase.SetTransform(this->transform);
    neck.SetTransform(this->transform);
    arms.SetTransform(this->transform);
    pelvis.SetTransform(this->transform);
}

void Body::PlayIdleBodyTransform(float dt)
{
    PlayBodyBob(dt);
    PlayBodyWiggle(dt);
}

void Body::PlayBodyWiggle(float dt)
{
    nextBodyWiggle -= dt;

    if (nextBodyWiggle <= 0.0f && !bodyWiggling)
    {
        bodyWiggling = true;
        bodyWiggleTimer = 0.0f;
        bodyWiggleAmplitude = (float)GetRandomValue(5, 10);
        nextBodyWiggle = (float)GetRandomValue(5, 7);
        bodyWiggleFrequency = (float)GetRandomValue(5, 20);
    }

    if (bodyWiggling)
    {
        bodyWiggleTimer += dt;

        transform.rotation = sin(bodyWiggleTimer * bodyWiggleFrequency) * bodyWiggleAmplitude;

        // Gradually reduce the wiggle until the body settles.
        bodyWiggleAmplitude -= 8.0f * dt;

        if (bodyWiggleAmplitude <= 0.0f)
        {
            bodyWiggling = false;
            transform.rotation = homeTransform.rotation;
        }
        bodyBase.SetTransform(transform);
        neck.SetTransform(transform);
        pelvis.SetTransform(transform);
        arms.SetTransform(transform);
    }
}

// Move the body in a slow, organic elliptical motion.
void Body::PlayBodyBob(float dt)
{
    bodyBobAngle += dt * bodyBobSpeed * bodyBobDirection;

    randomBodyBobSignTimer -= dt;

    // Periodically randomise the bobbing direction and movement.
    if (randomBodyBobSignTimer <= 0)
    {
        bodyBobDirection *= -1;
        randomBodyBobSignTimer = (float)GetRandomValue(5, 10);
        bodyBobRadiusX = GetRandomValue(3, 8);
        bodyBobRadiusY = GetRandomValue(2, 6);
        bodyBobSpeed = GetRandomValue(6, 14) / 10.0f;
    }

    bodyBobOffset.x = cos(bodyBobAngle) * bodyBobRadiusX;
    bodyBobOffset.y = sin(bodyBobAngle) * bodyBobRadiusY;

    transform.position.x = homeTransform.position.x + bodyBobOffset.x;
    transform.position.y = homeTransform.position.y + bodyBobOffset.y;

    bodyBase.SetTransform(transform);
    neck.SetTransform(transform);
    pelvis.SetTransform(transform);
    arms.SetTransform(transform);
}

Head& Body::GetHead()
{
    return neck.GetHead();
}

/*
void Body::SwingArm(std::string side,  bool swing)
{
    arms.SwingArm(side, swing);
}*/


