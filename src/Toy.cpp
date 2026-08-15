#include "Toy.h"
#include "raylib.h"

void Toy::Initialise()
{
    position = Vector2(300,200);
    Sprite::SetPosition(position);

    // Load the Toy sprite sheet.
    texture = LoadTexture("assets/images/Toys/ball.png");

    // Sprite sheet layout.
    const int COLUMNS = 1;
    const int ROWS = 1;

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
    scale = 1;
}

void Toy::Update(float dt)
{
    Sprite::Update(dt);
}

void Toy::SetPosition(Vector2 newPosition)
{
    position = newPosition;
    Sprite::SetPosition(position);
}

Vector2 Toy::GetPosition()
{
    return position;
}