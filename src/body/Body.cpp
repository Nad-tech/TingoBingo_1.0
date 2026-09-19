#include "body/Body.h"
#include <cmath>
#include "Emotion.h"

// Initialise the body's transform and idle animation state.
Body::Body(BodyDimensions& dimensions) :
    dimensions(dimensions),
    transform(), 
    bodyBase(dimensions),
    neck(dimensions),
    pelvis(dimensions),
    arms(dimensions),
    homeAnchorPoint(0,0),    
    homeRotation(0.0f),
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

// Initialise every component that makes up the robot's body.
void Body::Initialise()
{
    bodyBase.Initialise();
    neck.Initialise();
    arms.Initialise();
    pelvis.Initialise();
}

// Release resources used by each body component.
void Body::Shutdown()
{
    neck.Shutdown();
    bodyBase.Shutdown();
    arms.Shutdown();
    pelvis.Shutdown();
}

// Update every animated body component.
void Body::Update(float dt, bool speaking, Emotion emotion)
{
    neck.Update(dt, speaking, emotion);
    bodyBase.Update(dt);
    arms.Update(dt);
    pelvis.Update(dt);
    
    //PlayIdleBodyTransform(dt);
}

void Body::Draw() const
{
    //pelvis.Draw();
    bodyBase.Draw();
    //arms.Draw();
    //neck.Draw();
}

void Body::SetTransform(MyTransform transform)
{
    this->transform = transform;

    bodyBase.SetTransform(this->transform);

    //neck.SetTransform(this->transform);

    //arms.SetTransform(this->transform);

    //pelvis.SetTransform(this->transform);
}

MyTransform Body::GetTransform() const
{
    return transform;
}

void Body::SetRotation(float rotation)
{
    transform.rotation = rotation;

    bodyBase.SetRotation(rotation);
    arms.SetRotation(rotation);

    pelvis.SetRotation(rotation);
    neck.SetRotation(rotation);
}

float Body::GetRotation()
{
    return transform.rotation;
}

/*void Body::PlayIdleBodyTransform(float dt)
{
    PlayBodyBob(dt);
    ApplyAnchorPoint(anchorPoint);

    PlayBodyWiggle(dt);
    ApplyRotation(rotation);
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

        rotation = sin(bodyWiggleTimer * bodyWiggleFrequency) * bodyWiggleAmplitude;

        // Gradually reduce the wiggle until the body settles.
        bodyWiggleAmplitude -= 8.0f * dt;

        if (bodyWiggleAmplitude <= 0.0f)
        {
            bodyWiggling = false;
            rotation = homeRotation;
        }
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

    anchorPoint.x = homeAnchorPoint.x + bodyBobOffset.x;
    anchorPoint.y = homeAnchorPoint.y + bodyBobOffset.y;
}*/

Head& Body::GetHead()
{
    return neck.GetHead();
}

/*void Body::SwingArm(std::string side,  bool swing)
{
    arms.SwingArm(side, swing);
}

Vector2 Body::GetHeadWorldPosition()
{
    return neck.GetHead().GetWorldPosition();
}*/
