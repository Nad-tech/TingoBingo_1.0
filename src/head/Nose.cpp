#include "head/Nose.h"
#include "Constants.h"

void Nose::Initialise() 
{
    texture = LoadTexture("assets/images/TingoBingo/head/nose.png");
    const int COLUMNS = 4;
    const int ROWS = 1;

    const int FRAME_WIDTH = texture.width / COLUMNS;
    const int FRAME_HEIGHT = texture.height / ROWS;

    const int TOTAL_FRAMES = COLUMNS * ROWS;
    
    const float ROTATION = 0.0f;
    const float FRAME_DURATION = 0.08f;


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

void Nose::Update(float dt)
{
    Sprite::Update(dt);//Update the timer
}

void Nose::PlayWiggle()
{
    if (!animation.IsPlaying())
    {
        animation.Play(0, 3);
    }
}