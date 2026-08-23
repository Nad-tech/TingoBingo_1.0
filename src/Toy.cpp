#include "Toy.h"
#include "raylib.h"
#include <cmath>

int FRAME_WIDTH;
int FRAME_HEIGHT;

void Toy::Initialise()
{
    position = Vector2(0, 0);

    // Load the Toy sprite sheet.
    texture = LoadTexture(textureFilename.c_str());

    // Sprite sheet layout.
    const int COLUMNS = 1;
    const int ROWS = 1;

    // Calculate the size of a single animation frame.
    FRAME_WIDTH = texture.width / COLUMNS;
    FRAME_HEIGHT = texture.height / ROWS;

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

    collisionBox = Rectangle
                        (
                            position.x - FRAME_WIDTH/2.0f, 
                            position.y - FRAME_HEIGHT/2.0f, 
                            FRAME_WIDTH, 
                            FRAME_HEIGHT
                        );
}

void Toy::SetTextureFilename(std::string textureFileName)
{
    this->textureFilename = textureFileName;
}


void Toy::UpdateToy(float dt, Vector2 mousePosition, bool mousePressed)
{
    Sprite::Update(dt);

    float dx = abs(position.x - mousePosition.x);
    float dy = abs(position.y - mousePosition.y);

    bool xInRange = dx >= 0 && dx <= 40;
    bool yInrange = dy >= 0 && dy <= 40;

    if(xInRange && yInrange)
    {
        if(mousePressed)
        {
            dragging = !dragging;
        }
    }

    if(dragging)
    {
        position = mousePosition;
    }

    collisionBox.x = position.x - FRAME_WIDTH/2.0f;
    collisionBox.y = position.y - FRAME_HEIGHT/2.0f;
}

bool Toy::IsDragging() const
{
    return dragging;
}

void Toy::DrawCollisionBox()
{
    DrawRectangle
        (
            collisionBox.x, 
            collisionBox.y, 
            collisionBox.width, 
            collisionBox.height,
            RED
        );
}

Rectangle Toy::GetCollisionBox()
{
    return collisionBox;
}

void Toy::SetName(std::string name)
{
    toyName = name;
}

std::string Toy::GetName()
{
    return toyName;
}