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
    head.SetBodyDimensions(
        bodyBase.GetFrameWidth(), 
        bodyBase.GetFrameHeight()
    );
    head.Initialise();
    

    leftArm.SetBodyDimensions(
        bodyBase.GetFrameWidth(), 
        bodyBase.GetFrameHeight(),
        "left"
    );
    leftArm.Initialise();
    

    rightArm.SetBodyDimensions(
        bodyBase.GetFrameWidth(), 
        bodyBase.GetFrameHeight(),
        "right"
    );
    rightArm.Initialise();
    
    leftLeg.SetBodyDimensions(
        bodyBase.GetFrameWidth(), 
        bodyBase.GetFrameHeight(),
        "left"
    );
    leftLeg.Initialise();

    rightLeg.SetBodyDimensions(
        bodyBase.GetFrameWidth(), 
        bodyBase.GetFrameHeight(),
        "right"
    );
    rightLeg.Initialise();
}

// Release resources used by each body component.
void Body::Shutdown()
{
    head.Shutdown();
    bodyBase.Shutdown();
    leftArm.Shutdown();
    rightArm.Shutdown();
    leftLeg.Shutdown();
    rightLeg.Shutdown();
}

// Update every animated body component.
void Body::Update(float dt, bool speaking, Emotion emotion)
{
    head.Update(dt, speaking, emotion);
    bodyBase.Update(dt);
    leftArm.Update(dt);
    rightArm.Update(dt);
    leftLeg.Update(dt);
    rightLeg.Update(dt);
    
    PlayIdleBodyTransform(dt);
}

void Body::Draw() const
{
    leftArm.Draw();
    rightArm.Draw();
    leftLeg.Draw();
    rightLeg.Draw();
    
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

    head.SetAnchorPoint(
            {
                anchorPoint.x + headOffset.x,
                anchorPoint.y + headOffset.y
            });

    leftArm.SetAnchorPoint(
            {
                anchorPoint.x + leftArmOffset.x,
                anchorPoint.y + leftArmOffset.y
            });
    
    rightArm.SetAnchorPoint(
            {
                anchorPoint.x + rightArmOffset.x,
                anchorPoint.y + rightArmOffset.y
            });

    leftLeg.SetAnchorPoint(
            {
                anchorPoint.x + leftLegOffset.x,
                anchorPoint.y + leftLegOffset.y
            });
    
    rightLeg.SetAnchorPoint(
            {
                anchorPoint.x + rightLegOffset.x,
                anchorPoint.y + rightLegOffset.y
            });
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
    leftArm.SetRotation(rotation);
    rightArm.SetRotation(rotation);
    leftLeg.SetRotation(rotation);
    rightLeg.SetRotation(rotation);
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
        bodyWiggleAmplitude = (float)GetRandomValue(10, 20);
        nextBodyWiggle = (float)GetRandomValue(5, 7);
        bodyWiggleFrequency = (float)GetRandomValue(10, 40);
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