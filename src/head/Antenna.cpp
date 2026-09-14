//====================================================
// Antenna.cpp
//
// Handles the robot's antenna sprite and animation.
// The antenna can play a short wiggle animation when
// triggered.
//====================================================

#include "Body/Head/Antenna.h"
#include "Constants.h"
#include "Animation.h"

void Antenna::Initialise()
{
    // Load the antenna sprite sheet.
    texture = LoadTexture("assets/images/TingoBingo/head/antenna.png");

    // Sprite sheet layout.
    const int COLUMNS = 4;
    const int ROWS = 2;

    // Calculate the size of a single animation frame.
    const int FRAME_WIDTH = texture.width / COLUMNS;
    const int FRAME_HEIGHT = texture.height / ROWS;

    const int TOTAL_FRAMES = COLUMNS * ROWS;

    // Animation settings.
    const float ROTATION = 0.0f;
    const float FRAME_DURATION = 0.06f;

    // Initialise the animation using the sprite sheet information.
    animation.Initialise
    (
        FRAME_WIDTH,
        FRAME_HEIGHT,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    rotation = ROTATION;
    scale = SCALE;

    localPositionOffset =
    {
        FRAME_WIDTH / 2.0f,
        FRAME_HEIGHT / 2.0f
        + bodyHeight / 2.0f
        + headHeight / 2.0f
        + neckHeight
        + topOfHeadOffset
    };

    anchorOffset = localPositionOffset;
}

void Antenna::Update(float dt)
{
     // Update the base sprite behaviour before handling antenna animation.
    Sprite::Update(dt);
    
    //Idle behavior
    //Wiggle the antenna at random intervals
    antennaAnimationTimer += dt;

    if (antennaAnimationTimer > nextAntennaAnimation)
    {
        animation.Play(0, 7, AnimationPriority::Idle);
        antennaAnimationTimer = 0.0f;
        nextAntennaAnimation = GetRandomValue(1000, 5000) / 1000.0f;
    }
}

void Antenna::SetBodyHeadNeckDimensions(
    float bW, float bH, 
    float hW, float hH, 
    float nW, float nH 
)
{
    // Store the supplied body dimensions.
    bodyWidth = bW;
    bodyHeight = bH;

    // Store the supplied head dimensions.
    headWidth = hW;
    headHeight = hH;

    neckWidth = nW;
    neckHeight = nH;
}
