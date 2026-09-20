#include "body/Legs/Thigh.h"
#include "Constants.h"
#include <string>

// Load the head sprite and initialise its animation.
Thigh::Thigh(BodyDimensions& dimensions, std::string side) :
    dimensions(dimensions),
    side(side)
{}

void Thigh::Initialise()
{
    //texture = LoadTexture("assets/images/TingoBingo/body/Leg.png");

    // Sprite sheet layout.
    const int COLUMNS = 1;
    const int ROWS = 1;

    // Calculate the size of a single animation frame.
    dimensions.thighWidth = 80.0f; //texture.width / COLUMNS;
    dimensions.thighHeight = 250.0f; //texture.height / ROWS;

    const int TOTAL_FRAMES = COLUMNS * ROWS;

    // Animation settings.
    //const float ROTATION = 0.0f;
    const float FRAME_DURATION = 0.02f;

    // Initialise the animation using the sprite sheet information.
    animation.Initialise
    (
        dimensions.thighWidth,
        dimensions.thighHeight,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    /*
    rotation = ROTATION;
    scale = SCALE;

    if(side == "left")
    {
        anchorOffset = {
            dimensions.bodyWidth / 2.0f - dimensions.thighWidth / 2.0f, 
            dimensions.bodyHeight + dimensions.pelvisHeight / 2.0f
        };
    }
    else if(side == "right")
    {
        anchorOffset = {
            -dimensions.bodyWidth / 2.0f + dimensions.thighWidth / 2.0f, 
            dimensions.bodyHeight + dimensions.pelvisHeight / 2.0f
        };
    }*/
}

// Return the current head animation frame.
int Thigh::GetFrame() const
{
    return animation.GetFrame();
}

// Apply a rotation transform to the head sprite.
void Thigh::SetRotation(float rotation)
{
    //Sprite::SetRotation(rotation);
}

void Thigh::Draw() const
{/*
    Rectangle thigh =
    {
        anchorPoint.x,
        anchorPoint.y,
        dimensions.thighWidth * scale,
        dimensions.thighHeight * scale
    };

    Vector2 drawAnchorOffset = {
        dimensions.thighWidth * scale / 2.0f - anchorOffset.x * scale,
        dimensions.thighHeight * scale / 2.0f - anchorOffset.y * scale
    };

    DrawRectanglePro(
        thigh,
        drawAnchorOffset,
        rotation,
        CARDBOARD_DARK
    ); 

    DrawCircle(anchorPoint.x, anchorPoint.y, 10, RED);*/
}