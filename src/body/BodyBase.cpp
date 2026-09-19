#include "body/BodyBase.h"

#include "Constants.h"
#include <iostream>

BodyBase::BodyBase(BodyDimensions& dimensions) : 
            dimensions(dimensions)
{
}

// Load the head sprite and initialise its animation.
void BodyBase::Initialise()
{
    texture = LoadTexture("assets/images/TingoBingo/body/BodyBase.png");

    // Sprite sheet layout.
    const int COLUMNS = 1;
    const int ROWS = 1;

    // Calculate the size of a single animation frame.
    dimensions.bodyWidth = texture.width / COLUMNS;
    dimensions.bodyHeight = texture.height / ROWS;

    const int TOTAL_FRAMES = COLUMNS * ROWS;

    // Animation settings.
    const float ROTATION = 0.0f;
    const float FRAME_DURATION = 0.02f;

    // Initialise the animation using the sprite sheet information.
    animation.Initialise
    (
        dimensions.bodyWidth,
        dimensions.bodyHeight,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );
}

// Return the current head animation frame.
int BodyBase::GetFrame() const
{
    return animation.GetFrame();
}

// Apply a rotation transform to the head sprite.
void BodyBase::SetRotation(float rotation)
{
    this->transform.rotation = rotation;
    Sprite::SetRotation(this->transform.rotation);
}

void BodyBase::SetTransform(MyTransform transform)
{
    this->transform = transform;
    Sprite::SetTransform(this->transform);
}
