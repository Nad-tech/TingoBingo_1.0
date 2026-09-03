#include "body/BodyBase.h"

#include "Constants.h"

// Load the head sprite and initialise its animation.
void BodyBase::Initialise()
{
    texture = LoadTexture("assets/images/TingoBingo/body/BodyBase.png");

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

    anchorOffset = {FRAME_WIDTH / 2.0f, FRAME_HEIGHT / 2.0f};
}

// Return the current head animation frame.
int BodyBase::GetFrame() const
{
    return animation.GetFrame();
}

// Apply a rotation transform to the head sprite.
void BodyBase::SetRotation(float rotation)
{
    Sprite::SetRotation(rotation);
}

float BodyBase::GetFrameWidth() const
{
    return animation.GetFrameWidth();
}

float BodyBase::GetFrameHeight() const
{
    return animation.GetFrameHeight();
}

