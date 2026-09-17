#include "Body/Pelvis.h"

Pelvis::Pelvis(BodyDimensions& dimensions) :
    dimensions(dimensions)
{}
void Pelvis::Initialise()
{
    dimensions.pelvisWidth = 240.0f;
    dimensions.pelvisHeight = 100.0f;

    rotation = 0;
    scale = SCALE;

    anchorOffset = {
        0,
        dimensions.bodyHeight / 2.0f +
        dimensions.pelvisHeight / 2.0f
    };
}

void Pelvis::Update(float dt)
{
    Sprite::Update(dt);
}

void Pelvis::Draw() const
{
    Rectangle pelvis =
    {
        anchorPoint.x,
        anchorPoint.y,
        dimensions.pelvisWidth * scale,
        dimensions.pelvisHeight * scale
    };

    Vector2 drawAnchorOffset = {
        dimensions.pelvisWidth * scale / 2.0f - anchorOffset.x * scale,
        dimensions.pelvisHeight * scale / 2.0f - anchorOffset.y * scale
    };

    DrawRectanglePro(
        pelvis,
        drawAnchorOffset,
        rotation,
        BROWN
    );
}

void Pelvis::SetRotation(float rotation)
{
    this->rotation = rotation;
}

void Pelvis::SetAnchorPoint(Vector2 anchorPoint)
{
    this->anchorPoint = anchorPoint;
}
void Pelvis::Shutdown()
{

}