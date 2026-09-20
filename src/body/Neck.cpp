#include "Body/Neck.h"
#include "raylib.h"

Neck::Neck(BodyDimensions& dimensions) : 
    Shape(dimensions),
    positionOffset(),
    head(dimensions)
{
}

void Neck::Initialise() 
{
    dimensions.neckWidth = 50.0f;
    dimensions.neckHeight = 30.0f;

    head.Initialise();

    positionOffset = {
        0, 
        dimensions.bodyHeight / 2.0f + dimensions.neckHeight / 2.0f
    };
}

void Neck::Update(float dt, bool speaking, Emotion emotion) {
    head.Update(dt, speaking, emotion);
}

void Neck::Draw() const
{
    Shape::Draw();
    head.Draw();
}

void Neck::SetTransform(MyTransform parentTransform)
{
    transform.position =
    {
        parentTransform.position.x + positionOffset.x,
        parentTransform.position.y + positionOffset.y
    };

    transform.pivot =
    {
        0,
        -positionOffset.y
    };
    
    transform.rotation = parentTransform.rotation;
    transform.scale = parentTransform.scale;

    Shape::SetTransform(transform);
    head.SetTransform(transform);
}

Head& Neck::GetHead()
{
    return head;
}

void Neck::Shutdown()
{
    head.Shutdown();
}