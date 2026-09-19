#include "Body/Arms/Elbow.h"
#include <cmath>
#include <iostream>

Elbow::Elbow(BodyDimensions& dimensions, std::string side) :
    dimensions(dimensions),
    side(side)
{}

void Elbow::Initialise()
{
    dimensions.elbowWidth = 50.0f;
    dimensions.elbowHeight = 50.0f;

    //rotation = 0.0f;

    //scale = SCALE;
}

void Elbow::Update(float dt)
{
    Sprite::Update(dt);
}

void Elbow::Draw()const 
{
    /*Rectangle elbow = {
        anchorPoint.x,
        anchorPoint.y,
        dimensions.elbowWidth * SCALE,
        dimensions.elbowHeight * SCALE
    };

    Vector2 localPivot =
    {
        dimensions.elbowWidth / 2.0f,
        0
    };

    DrawRectanglePro(
        elbow,
        localPivot,
        rotation + localRotation,
        WHITE
    );*/
}

int Elbow::GetFrame() const
{
    return 0;
}

void Elbow::SetRotation(float rotation) {
    //this->rotation = rotation;
}