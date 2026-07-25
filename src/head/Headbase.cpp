#include "head/Headbase.h"
#include "Constants.h"

void Headbase::Initialise()
{
    texture = LoadTexture("assets/images/TingoBingo/head/HeadBase.png");
    const int COLUMNS = 1;
    const int ROWS = 1;

    const int FRAME_WIDTH = texture.width / COLUMNS;
    const int FRAME_HEIGHT = texture.height / ROWS;

    const int TOTAL_FRAMES = COLUMNS * ROWS;
    
    const float ROTATION = 0.0f;
    const float FRAME_DURATION = 0.02f;

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
}

int Headbase::GetFrame() const
{
    return animation.GetFrame();
}

void Headbase::RotateLeft()
{
    animation.PreviousFrame();
}

void Headbase::RotateRight()
{
    animation.NextFrame();
}

void Headbase::ReturnToCentre()
{
    int frame = animation.GetFrame();
    int halfTurn = animation.GetTotalFrames() / 2;

    if (frame == 0)
        return;

    // Decide which way is shorter.
    if (frame < halfTurn)
    {
        animation.PreviousFrame();
    }
    else
    {
        animation.NextFrame();
    }
}

void Headbase::SetRotation(float rotation)
{
    Sprite::SetRotation(rotation);
}