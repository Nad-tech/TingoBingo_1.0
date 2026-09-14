#include "Body/Neck.h"
#include "raylib.h"

void Neck::Initialise() 
{
    head.SetBodyNeckDimensions(
        bodyWidth,
        bodyHeight,
        NECK_WIDTH,
        NECK_HEIGHT
    );
    head.Initialise();

    rotation = 0.0f;
    scale = SCALE;

    anchorOffset = {
        0, 
        -bodyHeight / 2.0f - 
        NECK_HEIGHT / 2.0f
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
        NECK_WIDTH * scale,
        NECK_HEIGHT * scale
    };

    Vector2 drawAnchorOffset = {
        NECK_WIDTH * scale / 2.0f - anchorOffset.x * scale,
        NECK_HEIGHT * scale / 2.0f - anchorOffset.y * scale
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
void Neck::SetBodyDimensions(float bW, float bH)
{
    bodyWidth = bW;
    bodyHeight = bH;

    head.SetBodyNeckDimensions(bW, bH, NECK_WIDTH, NECK_HEIGHT);
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