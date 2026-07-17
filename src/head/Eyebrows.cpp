#include "head/Eyebrows.h"

void Eyebrows::Initialise() 
{
    texture = LoadTexture("assets/images/TingoBingo/head/eyebrows.png");

    position = { 0.0f, 0.0f };
    rotation = 0.0f;
    scale = 1.0f;
}

void Eyebrows::Update(float dt)
{
    (void)dt;
}

void Eyebrows::Draw() const 
{

}