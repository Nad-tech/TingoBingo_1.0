#include "head/Mouth.h"

void Mouth::Initialise() 
{
    texture = LoadTexture("assets/images/TingoBingo/head/mouth.png");

    position = { 0.0f, 0.0f };
    rotation = 0.0f;
    scale = 1.0f;
}

void Mouth::Update(float dt)
{
    (void)dt;
}

void Mouth::Draw() const 
{

}