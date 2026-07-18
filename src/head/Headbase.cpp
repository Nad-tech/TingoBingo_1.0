#include "head/Headbase.h"
#include "Constants.h"

void Headbase::Initialise() 
{
    texture = LoadTexture("assets/images/TingoBingo/head/headbase.png");
    rotation = 0.0f;
    scale = 1.0f;
    frame = 0;
    frameTimer = 0;
}

void Headbase::IncrementFrame() {
    frame = (frame + 1) % 8;
}

void Headbase::Update(float dt)
{
    frameTimer += dt;
    if(frameTimer >= 0.4) 
    {
        IncrementFrame();
        frameTimer = 0;
    }
}

void Headbase::Draw() const 
{
    int columns = 4;

    float column = frame % columns;
    float row    = frame / columns;

    Rectangle source =
    {
        column * SPRITESHEET_FRAME_SIZE,
        row * SPRITESHEET_FRAME_SIZE,
        SPRITESHEET_FRAME_SIZE,
        SPRITESHEET_FRAME_SIZE
    };

    Rectangle destination = {
        position.x,
        position.y,
        source.width * scale,
        source.height * scale
    };

    Vector2 origin = {
        0.0f,
        0.0f
    };

    DrawTexturePro(
        texture,
        source,
        destination,
        origin,
        rotation,
        WHITE
    );
}

