#include "head/Eyes.h"

void Eyes::Initialise() 
{
    texture = LoadTexture("assets/images/TingoBingo/head/eyes.png");

    position = { 0.0f, 0.0f };
    rotation = 0.0f;
    scale = 1.0f;
}

void Eyes::Update(float dt)
{
    (void)dt;
}

void Eyes::Draw() const 
{
    
}