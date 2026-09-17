#include "body/Legs/Thigh.h"
#include "Constants.h"
#include <string>

// Load the head sprite and initialise its animation.
Thigh::Thigh(BodyDimensions& dimensions) :
    dimensions(dimensions)
{}

void Thigh::Initialise()
{
    //texture = LoadTexture("assets/images/TingoBingo/body/Leg.png");

    // Sprite sheet layout.
    const int COLUMNS = 1;
    const int ROWS = 1;

    // Calculate the size of a single animation frame.
    dimensions.thighWidth = texture.width / COLUMNS;
    dimensions.thighHeight = texture.height / ROWS;

    const int TOTAL_FRAMES = COLUMNS * ROWS;

    // Animation settings.
    const float ROTATION = 0.0f;
    const float FRAME_DURATION = 0.02f;

    // Initialise the animation using the sprite sheet information.
    animation.Initialise
    (
        dimensions.thighWidth,
        dimensions.thighHeight,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    rotation = ROTATION;
    scale = SCALE;

    if(side == "left")
    {
        anchorOffset = {
            0, 
            0
        };
    }
    else if(side == "right")
    {
        anchorOffset = {
            0, 
            0
        };
    }
}

// Return the current head animation frame.
int Thigh::GetFrame() const
{
    return animation.GetFrame();
}

// Apply a rotation transform to the head sprite.
void Thigh::SetRotation(float rotation)
{
    Sprite::SetRotation(rotation);
}
