#include "Object.h"

void Object::Initialise() 
{
    texture = LoadTexture("assets/images/TingoBingo/head/antenna.png");

    position = { 0.0f, 0.0f };
    rotation = 0.0f;
    scale = 1.0f;
}

void Object::Update(float dt)
{
    (void)dt;
}

void Object::Draw() const 
{
    DrawCircle(10,10,10,RED);
}

