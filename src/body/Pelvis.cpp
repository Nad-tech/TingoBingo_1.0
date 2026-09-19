#include "Body/Pelvis.h"
#include "raymath.h"

Pelvis::Pelvis(BodyDimensions& dimensions) :
    dimensions(dimensions),
    legs(dimensions)
{}
void Pelvis::Initialise()
{
    dimensions.pelvisWidth = 260.0f;
    dimensions.pelvisHeight = 70.0f;

    /*rotation = 0;
    scale = SCALE;

    anchorOffset = {
        0,
        dimensions.bodyHeight / 2.0f +
        dimensions.pelvisHeight / 2.0f
    };*/

    legs.Initialise();
}

void Pelvis::Update(float dt)
{
    Sprite::Update(dt);
    legs.Update(dt);
}

void Pelvis::Draw() const
{
    /*Rectangle pelvis =
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

    legs.Draw();

    DrawRectanglePro(
        pelvis,
        drawAnchorOffset,
        rotation,
        BROWN
    );*/
    //DrawCircle(anchorPoint.x + anchorOffset.x*scale, anchorPoint.y + anchorOffset.y*scale, 10, RED);
}

void Pelvis::SetRotation(float rotation)
{
    //this->rotation = rotation;
    legs.SetRotation(rotation);

}

void Pelvis::SetAnchorPoint(Vector2 anchorPoint)
{
    //this->anchorPoint = anchorPoint;

    legs.SetAnchorPoint(anchorPoint);
}

void Pelvis::Shutdown()
{
    legs.Shutdown();
}