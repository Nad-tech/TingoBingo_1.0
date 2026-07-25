#include "head/Pupil.h"
#include "raylib.h"
#include "Constants.h"

void Pupil::Initialise() 
{
    texture = LoadTexture("assets/images/TingoBingo/head/pupil.png");
    const int COLUMNS = 1;
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

void Pupil::Update(float dt)
{
    Sprite::Update(dt);//Update the timer
}
