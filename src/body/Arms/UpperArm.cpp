#include "body/Arms/UpperArm.h"
#include "Constants.h"
#include <cmath>
#include <iostream>

// Construct the upper arm using the shared body dimensions
// and the side of the body that the arm belongs to.
UpperArm::UpperArm(BodyDimensions& dimensions, std::string side)
    : dimensions(dimensions),
      side(side),
      elbow(dimensions, side)
{
}

// Initialise the upper arm and its animation.
void UpperArm::Initialise()
{
    // Load the upper arm texture.
    texture = LoadTexture("assets/images/TingoBingo/body/Arm.png");

    // Sprite sheet layout.
    // The upper arm currently consists of a single frame.
    const int COLUMNS = 1;
    const int ROWS = 1;

    // Calculate the dimensions of a single animation frame
    // from the loaded texture.
    dimensions.upperArmWidth = texture.width / COLUMNS;
    dimensions.upperArmHeight = texture.height / ROWS;

    // Debug output for checking the calculated dimensions.
     std::cout << dimensions.upperArmWidth << " * "
               << dimensions.upperArmHeight << "\n";

    // Calculate the total number of animation frames.
    const int TOTAL_FRAMES = COLUMNS * ROWS;

    // Animation settings.
    const float ROTATION = 0.0f;
    const float FRAME_DURATION = 0.02f;

    // Initialise the animation using the calculated frame dimensions.
    animation.Initialise
    (
        dimensions.upperArmWidth,
        dimensions.upperArmHeight,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    // Set the initial rotation and drawing scale.
    /*rotation = ROTATION;
    scale = SCALE;

    // Position the upper arm relative to its parent shoulder.
    //
    // The Shoulder passes its world-space position to the
    // UpperArm through SetAnchorPoint().
    //
    // localPositionOffset therefore represents the upper arm's
    // position relative to the shoulder rather than the body.
    //
    // X:
    //     Move the anchor to the centre of the upper arm.
    //
    // Y:
    //     Position the upper arm below the shoulder using the
    //     shared shoulder height.
    anchorOffset = {
        dimensions.upperArmWidth / 2.0f,
        dimensions.shoulderHeight / 2.0f
    };

    elbow.Initialise();*/
}

// Update the upper arm and its animation state.
void UpperArm::Update(float dt)
{
    Sprite::Update(dt);

    /*Vector2 offset = anchorOffset;

    float radians = rotation * DEG2RAD;

    Vector2 rotatedOffset =
    {
        (offset.x * cosf(radians) -
         offset.y * sinf(radians)),

        offset.x * sinf(radians) +
        offset.y * cosf(radians)
    };

    armAnchorPosition =
    {
        anchorPoint.x + rotatedOffset.x * scale,
        anchorPoint.y + rotatedOffset.y * scale
    };

    Vector2 elbowOffset =
    {
        0,
        dimensions.upperArmHeight
    };

    Vector2 rotatedElbowOffset =
    {
        elbowOffset.x * cosf(radians) -
        elbowOffset.y * sinf(radians),

        elbowOffset.x * sinf(radians) +
        elbowOffset.y * cosf(radians)
    };

    Vector2 elbowAnchorPosition =
    {
        armAnchorPosition.x + rotatedElbowOffset.x * scale,
        armAnchorPosition.y + rotatedElbowOffset.y * scale
    };

    //elbow.SetAnchorPoint(elbowAnchorPosition);

    elbow.Update(dt);*/
}

// Return the current animation frame of the upper arm.
int UpperArm::GetFrame() const
{
    return animation.GetFrame();
}

// Set the upper arm's base rotation.
void UpperArm::SetRotation(float rotation)
{
    Sprite::SetRotation(rotation);
    elbow.SetRotation(rotation + localRotation);
}

// Draw the upper arm.
void UpperArm::Draw() const
{
    // Get the source rectangle for the current animation frame.
    Rectangle source = animation.GetSourceRectangle();
/*
    // Calculate the scaled dimensions of the current frame.
    float width = animation.GetFrameWidth() * scale;
    float height = animation.GetFrameHeight() * scale;

    Rectangle destination =
    {
        armAnchorPosition.x - width / 2.0f,
        armAnchorPosition.y,
        width,
        height
    };

    Vector2 origin =
    {
        width / 2.0f,
        0
    };

    DrawTexturePro(
        texture,
        source,
        destination,
        origin,
        rotation + localRotation,
        WHITE
    );

    elbow.Draw();*/
}

// Swing the upper arm between the supplied minimum
// and maximum angles.
void UpperArm::SwingArm(
    float dt,
    float swingMinAngle,
    float swingMaxAngle
)
{
    // Advance the swing timer based on elapsed time
    // and the configured swing speed.
    swingTime += dt * SWING_SPEED;

    // Keep the timer within one complete sine-wave cycle.
    if (swingTime >= 2.0f * PI)
    {
        swingTime -= 2.0f * PI;
    }

    // Normalised value used to convert the sine wave
    // into the requested swing angle range.
    float unitAngle = 0;

    // Reverse the swing direction for the left arm.
    if(side == "left")
    {
        unitAngle = -(sinf(swingTime) + 1.0f) / 2.0f;
    }

    // Use the normal swing direction for the right arm.
    if(side == "right")
    {
        unitAngle = (sinf(swingTime) + 1.0f) / 2.0f;
    }

    // Convert the normalised sine-wave value into the
    // requested rotation range.
    //
    // For example:
    //
    // swingMinAngle = 0
    // swingMaxAngle = 180
    //
    // produces a smooth swing between 0 and 180 degrees.
    localRotation =
        swingMinAngle +
        unitAngle * (swingMaxAngle - swingMinAngle);
}