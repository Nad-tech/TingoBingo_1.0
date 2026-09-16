#include "Body/Neck.h"
#include "raylib.h"

Neck::Neck(BodyDimensions& dimensions) : 
    dimensions(dimensions),
    head(dimensions)
{
}

void Neck::Initialise() 
{
    dimensions.neckWidth = 50.0f;
    dimensions.neckHeight = 30.0f;

    head.Initialise();

    rotation = 0.0f;
    scale = SCALE;

    anchorOffset = {
        0, 
        -dimensions.bodyHeight / 2.0f - 
        dimensions.neckHeight / 2.0f
    };
}

void Neck::Update(float dt, bool speaking, Emotion emotion) {
    head.Update(dt, speaking, emotion);
    Sprite::Update(dt);
}

void Neck::Draw() const
{
    Rectangle neck =
    {
        anchorPoint.x,
        anchorPoint.y,
        dimensions.neckWidth * scale,
        dimensions.neckHeight * scale
    };

    Vector2 drawAnchorOffset = {
        dimensions.neckWidth * scale / 2.0f - anchorOffset.x * scale,
        dimensions.neckHeight * scale / 2.0f - anchorOffset.y * scale
    };

    DrawRectanglePro(
        neck,
        drawAnchorOffset,
        rotation,
        BROWN
    );

    head.Draw();
}

void Neck::SetRotation(float rotation)
{
    this->rotation = rotation;
    head.SetRotation(rotation);
}

void Neck::SetAnchorPoint(Vector2 anchorPoint)
{
    this->anchorPoint = anchorPoint;

    head.SetAnchorPoint(anchorPoint);
}

Head& Neck::GetHead()
{
    return head;
}

void Neck::Shutdown()
{
    head.Shutdown();
}