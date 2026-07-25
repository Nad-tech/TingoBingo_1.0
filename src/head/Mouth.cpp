#include "head/Mouth.h"
#include "Constants.h"

void Mouth::Initialise() 
{
    texture = LoadTexture("assets/images/TingoBingo/head/mouth.png");

    const int COLUMNS = 3;
    const int ROWS = 1;

    const int FRAME_WIDTH = texture.width / COLUMNS;
    const int FRAME_HEIGHT = texture.height / ROWS;

    const int TOTAL_FRAMES = COLUMNS * ROWS;
    
    const float ROTATION = 0.0f;
    const float FRAME_DURATION = 1.0f;


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

void Mouth::Update(float dt)
{
    Sprite::Update(dt);//Update the timer
}

void Mouth::PlayIdleMouth()
{
    if (!animation.IsPlaying())
    {
        animation.Play(0, 2);
    } 
}