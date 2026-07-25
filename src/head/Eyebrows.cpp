#include "head/Eyebrows.h"
#include "Constants.h"

void Eyebrows::Initialise() 
{
    texture = LoadTexture("assets/images/TingoBingo/head/eyebrows.png");
    
    const int COLUMNS = 2;
    const int ROWS = 1;

    const int FRAME_WIDTH = texture.width / COLUMNS;
    const int FRAME_HEIGHT = texture.height / ROWS;

    const int TOTAL_FRAMES = COLUMNS * ROWS;
    
    const float ROTATION = 0.0f;
    const float FRAME_DURATION = 0.3f;


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

void Eyebrows::Update(float dt)
{
    Sprite::Update(dt);//Update the timer
}

void Eyebrows::PlayWiggle()
{
    if (!animation.IsPlaying())
    {
        animation.Play(0, 1);
    }
}