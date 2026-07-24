#include "head/Antenna.h"
#include "Constants.h"

void Antenna::Initialise() 
{
    texture = LoadTexture("assets/images/TingoBingo/head/antenna.png");
    const int COLUMNS = 4;
    const int ROWS = 2;

    const int FRAME_WIDTH = texture.width / COLUMNS;
    const int FRAME_HEIGHT = texture.height / ROWS;

    const int TOTAL_FRAMES = COLUMNS * ROWS;
    
    const float ROTATION = 0.0f;
    const float FRAME_DURATION = 0.06f;


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

void Antenna::Update(float dt)
{
    Sprite::Update(dt);//Update the timer

    blinkTimer += dt;

    if (blinkTimer >= nextBlink && !animation.IsPlaying())
    {
        animation.Play(0, 7);
        
        blinkTimer = 0.0f;
        nextBlink = GetRandomValue(1000,5000) / 1000.0f;
    }
}

