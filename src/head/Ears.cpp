#include "head/Ears.h"

void Ears::Initialise() 
{
    texture = LoadTexture("assets/images/TingoBingo/head/ears.png");

    position = { 0.0f, 0.0f };
    rotation = 0.0f;
    scale = 1.0f;
}

void Ears::Update(float dt)
{
    (void)dt;
}

void Ears::Draw() const 
{

}

