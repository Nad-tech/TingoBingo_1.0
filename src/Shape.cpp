

#include "Shape.h"
#include <cmath>

void Shape::Draw() const
{
    Vector2 screenPosition =
    {
        SCREEN_WIDTH / 2.0f + transform.position.x * transform.scale,
        SCREEN_HEIGHT / 2.0f - transform.position.y * transform.scale
    };

    Vector2 pivotScreen =
    {
        screenPosition.x + transform.pivot.x * transform.scale,
        screenPosition.y - transform.pivot.y * transform.scale
    };

    float scaledWidth = width * transform.scale;
    float scaledHeight = height * transform.scale;

    Rectangle rectangle = {
        pivotScreen.x,
        pivotScreen.y,
        scaledWidth,
        scaledHeight
    };

    Vector2 origin =
    {
        scaledWidth / 2.0f + transform.pivot.x * transform.scale,
        scaledHeight / 2.0f - transform.pivot.y * transform.scale
    };

    DrawRectanglePro(
        rectangle,
        origin,
        -transform.rotation,
        color
    );
}

void Shape::SetDimensions(float width, float height)
{
    this->width = width;
    this->height = height;
}

void Shape::Shutdown()
{
    
}

void Shape::SetTransform(MyTransform transform)
{
    this->transform = transform;
}
