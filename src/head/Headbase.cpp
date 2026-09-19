//====================================================
// HeadBase.cpp
//
// Handles the robot's main head sprite.
//
// The HeadBase is responsible for displaying the
// current head orientation and managing rotation
// between head frames.
//====================================================

#include "Body/Head/Headbase.h"
#include "Constants.h"
#include "raylib.h"

Headbase::Headbase(BodyDimensions& dimensions) : dimensions(dimensions)
{}

// Load the head sprite and initialise its animation.
void Headbase::Initialise()
{
    texture = LoadTexture("assets/images/TingoBingo/head/HeadBase.png");

    // Sprite sheet layout.
    const int COLUMNS = 1;
    const int ROWS = 1;

    // Calculate the size of a single animation frame.
    dimensions.headWidth = texture.width / COLUMNS;
    dimensions.headHeight = texture.height / ROWS;

    const int TOTAL_FRAMES = COLUMNS * ROWS;

    // Animation settings.
    const float ROTATION = 0.0f;
    const float FRAME_DURATION = 0.02f;

    // Initialise the animation using the sprite sheet information.
    animation.Initialise
    (
        dimensions.headWidth,
        dimensions.headHeight,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );
    /*
    rotation = ROTATION;
    scale = SCALE;

    anchorOffset = {
        dimensions.headWidth / 2.0f, 
        dimensions.headHeight + 
        (dimensions.bodyHeight / 2.0f) +
        (dimensions.neckHeight)
    };*/
}

// Return the current head animation frame.
int Headbase::GetFrame() const
{
    return animation.GetFrame();
}

// Apply a rotation transform to the head sprite.
void Headbase::SetRotation(float rotation)
{
    Sprite::SetRotation(rotation);
}

Vector2 Headbase::GetWorldPosition() const
{
   return {};/* {
    anchorPoint.x, 
    anchorPoint.y - 
    (dimensions.bodyHeight / 2.0f) * SCALE -
    (animation.GetFrameHeight() / 2) * SCALE -
    dimensions.neckHeight * SCALE
   }; */
}
