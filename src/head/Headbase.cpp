#include "head/Headbase.h"

void Headbase::Initialise() 
{
    texture = LoadTexture("assets/images/TingoBingo/head/headbase.png");

    position = { 100.0f, 0.0f };
    rotation = 0.0f;
    scale = 2.5f;
}

void Headbase::Update(float dt)
{
    (void)dt;
}

void Headbase::Draw() const 
{
    Rectangle source = {
        32.0f,
        32.0f,
        256.0f - 64.0f,
        256.0f - 32.0f
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

