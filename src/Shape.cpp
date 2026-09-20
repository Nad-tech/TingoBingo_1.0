

#include "Shape.h"
#include <cmath>

Shape::Shape(BodyDimensions& dimensions) :
    dimensions(dimensions)
{}

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

    float width = dimensions.neckWidth * transform.scale;
    float height = dimensions.neckHeight * transform.scale;

    Rectangle rectangle = {
        pivotScreen.x,
        pivotScreen.y,
        width,
        height
    };

    Vector2 origin =
    {
        width / 2.0f + transform.pivot.x * transform.scale,
        height / 2.0f - transform.pivot.y * transform.scale
    };

    DrawRectanglePro(
        rectangle,
        origin,
        transform.rotation,
        CARDBOARD_DARK
    );
}

void Shape::Shutdown()
{
    
}

void Shape::SetTransform(MyTransform transform)
{
    this->transform = transform;
}
