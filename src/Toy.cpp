#include "Toy.h"
#include "raylib.h"
#include <cmath>


int FRAME_WIDTH;
int FRAME_HEIGHT;


//====================================================
// Initialise
//
// Loads the toy's sprite and sets up its animation,
// transform, starting position and collision box.
//====================================================

void Toy::Initialise()
{
    // Start the toy at the origin.
    position = Vector2(0, 0);

    // Load the toy sprite sheet.
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

    // Create a collision rectangle centred on the toy.
    //
    // The rectangle is used by the interaction system
    // to determine when the toy overlaps with other objects.
    collisionBox = Rectangle
    (
        position.x - FRAME_WIDTH / 2.0f,
        position.y - FRAME_HEIGHT / 2.0f,
        FRAME_WIDTH,
        FRAME_HEIGHT
    );
}


//====================================================
// SetTextureFilename
//
// Sets the path to the image that will be loaded
// when the toy is initialised.
//====================================================

void Toy::SetTextureFilename(std::string textureFileName)
{
    this->textureFilename = textureFileName;
}


//====================================================
// UpdateToy
//
// Updates the toy's animation, mouse interaction,
// dragging state and collision box.
//====================================================

void Toy::UpdateToy(
    float dt,
    Vector2 mousePosition,
    bool mousePressed
)
{
    // Update the underlying sprite animation.
    Sprite::Update(dt);


    // Calculate the horizontal and vertical distance
    // between the mouse and the centre of the toy.
    float dx = abs(position.x - mousePosition.x);
    float dy = abs(position.y - mousePosition.y);


    // The mouse must be within 40 pixels of the toy
    // on both axes to interact with it.
    bool xInRange = dx >= 0 && dx <= 40;
    bool yInrange = dy >= 0 && dy <= 40;


    // Toggle dragging when the mouse is pressed while
    // the cursor is within the interaction range.
    if (xInRange && yInrange)
    {
        if (mousePressed)
        {
            dragging = !dragging;
        }
    }


    // While dragging, make the toy follow the mouse.
    if (dragging)
    {
        position = mousePosition;
    }


    // Keep the collision box centred on the toy's
    // current position after it has moved.
    collisionBox.x =
        position.x - FRAME_WIDTH / 2.0f;

    collisionBox.y =
        position.y - FRAME_HEIGHT / 2.0f;
}


//====================================================
// IsDragging
//
// Returns true while the toy is currently being
// dragged by the mouse.
//====================================================

bool Toy::IsDragging() const
{
    return dragging;
}


//====================================================
// DrawCollisionBox
//
// Draws the toy's collision rectangle for debugging.
// This can be useful when tuning interaction and
// collision behaviour.
//====================================================

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


// Return the toy's current collision rectangle.
Rectangle Toy::GetCollisionBox()
{
    return collisionBox;
}


// Set the name used to identify the toy.
void Toy::SetName(std::string name)
{
    toyName = name;
}


// Return the toy's name.
std::string Toy::GetName()
{
    return toyName;
}