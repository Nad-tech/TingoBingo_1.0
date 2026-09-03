#include "body/Leg.h"
#include "Constants.h"
#include <string>

// Load the head sprite and initialise its animation.
void Leg::Initialise()
{
    texture = LoadTexture("assets/images/TingoBingo/body/Leg.png");

    // Sprite sheet layout.
    const int COLUMNS = 1;
    const int ROWS = 1;

    // Calculate the size of a single animation frame.
    const int FRAME_WIDTH = texture.width / COLUMNS;
    const int FRAME_HEIGHT = texture.height / ROWS;

    const int TOTAL_FRAMES = COLUMNS * ROWS;

    // Animation settings.
    const float ROTATION = 0.0f;
    const float FRAME_DURATION = 0.02f;

    // Initialise the animation using the sprite sheet information.
    animation.Initialise
    (
        FRAME_WIDTH,
        FRAME_HEIGHT,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    rotation = ROTATION;
    scale = SCALE;

    if(side == "left")
    {
        origin = {
            bodyWidth / 2, 
            -bodyHeight / 2
        };
    }
    else if(side == "right")
    {
        origin = {
            -bodyWidth / 2 + FRAME_WIDTH, 
            -bodyHeight / 2
        };
    }
}

// Return the current head animation frame.
int Leg::GetFrame() const
{
    return animation.GetFrame();
}

// Apply a rotation transform to the head sprite.
void Leg::SetRotation(float rotation)
{
    Sprite::SetRotation(rotation);
}

void Leg::SetBodyDimensions(float width, float height, const std::string& side)
{
    bodyWidth = width;
    bodyHeight = height;
    this->side = side;
}