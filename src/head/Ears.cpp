#include "head/Ears.h"
#include "Constants.h"

void Ears::Initialise() 
{
    texture = LoadTexture("assets/images/TingoBingo/head/ears.png");

    const int COLUMNS = 5;
    const int ROWS = 1;

    const int FRAME_WIDTH = texture.width / COLUMNS;
    const int FRAME_HEIGHT = texture.height / ROWS;

    const int TOTAL_FRAMES = COLUMNS * ROWS;
    
    const float ROTATION = 0.0f;
    const float FRAME_DURATION = 0.09f;


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

void Ears::Update(float dt)
{
    Sprite::Update(dt);//Update the timer
}

void Ears::PlayWiggle()
{
    if (!animation.IsPlaying())
    {
        animation.Play(0, 4);
    }
}