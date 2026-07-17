#include "head/Antenna.h"

void Antenna::Initialise() 
{
    texture = LoadTexture("assets/images/TingoBingo/head/antenna.png");

    position = { 0.0f, 0.0f };
    rotation = 0.0f;
    scale = 1.0f;
}

void Antenna::Update(float dt)
{
    (void)dt;
}

void Antenna::Draw() const 
{

}

