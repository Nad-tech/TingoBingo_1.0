#include "body/Arm.h"
#include "Constants.h"

// Load the head sprite and initialise its animation.
void Arm::Initialise()
{
    texture = LoadTexture("assets/images/TingoBingo/body/Arm.png");

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

    // Position the arm anchor offset relative to the body anchor point based on which side it is on.
    if(side == "left")
    {
        anchorOffset = {
            bodyWidth / 2.0f + FRAME_WIDTH,
            bodyHeight / 2.0f
        }; 
    }
    else if(side == "right")
    {
        anchorOffset = {
            -bodyWidth / 2.0f,
            bodyHeight / 2.0f
        }; 
    }
}

// Return the current head animation frame.
int Arm::GetFrame() const
{
    return animation.GetFrame();
}

// Apply a rotation transform to the head sprite.
void Arm::SetRotation(float rotation)
{
    Sprite::SetRotation(rotation);
}

// Set the dimensions of the body to position the arm correctly relative to the body.
void Arm::SetBodyDimensions(float width, float height, std::string side)
{
    bodyWidth = width;
    bodyHeight = height;
    this->side = side; 
}