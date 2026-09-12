#include "body/Body.h"
#include <cmath>
#include "Emotion.h"

// Initialise the body's transform and idle animation state.
Body::Body() :
    rotation(0.0f),
    scale(0.0f),

    homeRotation(rotation),
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
{
}

// Initialise every component that makes up the robot's body.
void Body::Initialise()
{
    bodyBase.Initialise();
    
    //head.SetBodyDimensions() must be called before head.Initialise() 
    // so that the head can anchor itself correctly relative to the body
    //The same for arms and legs
    head.SetBodyDimensions(
        bodyBase.GetFrameWidth(), 
        bodyBase.GetFrameHeight()
    );
    head.Initialise();
    
    arms.SetBodyDimensions(
        bodyBase.GetFrameWidth(), 
        bodyBase.GetFrameHeight()
        );
    arms.Initialise();
    
    legs.SetBodyDimension(
        bodyBase.GetFrameWidth(), 
        bodyBase.GetFrameHeight()
    );
    legs.Initialise();
}

// Release resources used by each body component.
void Body::Shutdown()
{
    head.Shutdown();
    bodyBase.Shutdown();
    arms.Shutdown();
    legs.Shutdown();
}

// Update every animated body component.
void Body::Update(float dt, bool speaking, Emotion emotion)
{
    head.Update(dt, speaking, emotion);
    bodyBase.Update(dt);
    arms.Update(dt);
    legs.Update(dt);
    
    PlayIdleBodyTransform(dt);
}

void Body::Draw() const
{
    arms.Draw();
    
    legs.Draw();
    
    bodyBase.Draw();

    head.Draw();
}

void Body::SetAnchorPoint(Vector2 anchorPoint)
{
    this->homeAnchorPoint = anchorPoint;
    ApplyAnchorPoint(anchorPoint);
}

void Body::ApplyAnchorPoint(Vector2 anchorPoint)
{
    this->anchorPoint = anchorPoint;

    bodyBase.SetAnchorPoint(anchorPoint);

    head.SetAnchorPoint(anchorPoint);

    arms.SetAnchorPoint(anchorPoint);

    legs.SetAnchorPoint(anchorPoint);
}

Vector2 Body::GetAnchorPoint() const
{
    return anchorPoint;
}

void Body::SetRotation(float rotation)
{
    homeRotation = rotation;
    ApplyRotation(rotation);
}

void Body::ApplyRotation(float rotation)
{
    this->rotation = rotation;
   
    bodyBase.SetRotation(rotation);
    arms.SetRotation(rotation);

    legs.SetRotation(rotation);
    head.SetRotation(rotation);
}

float Body::GetRotation()
{
    return rotation;
}

void Body::PlayIdleBodyTransform(float dt)
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
}

Head& Body::GetHead()
{
    return head;
}

void Body::SwingArm(std::string side,  bool swing)
{
    arms.SwingArm(side, swing);
}

Vector2 Body::GetHeadWorldPosition() const
{
    return head.GetWorldPosition();
}
