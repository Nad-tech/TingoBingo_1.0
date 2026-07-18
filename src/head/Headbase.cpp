#include "head/Headbase.h"

void Headbase::Initialise() 
{
    texture = LoadTexture("assets/images/TingoBingo/head/headbase.png");
    rotation = 0.0f;
    scale = 1.0f;
}

void Headbase::Update(float dt)
{
    (void)dt;
}

void Headbase::Draw() const 
{
    Rectangle source = {
    0.0f,   // x: start 32 pixels from left
    0.0f,   // y: start 32 pixels from top
    256.0f,  // width of frame
    256.0f   // height of frame
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

