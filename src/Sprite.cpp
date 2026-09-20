//====================================================
// Sprite.cpp
//
// Provides a base class for drawable sprites.
//
// A Sprite stores its texture, anchor point, rotation,
// scale and animation. Derived classes only need to
// load their textures and configure their animations.
//====================================================

#include "Sprite.h"
#include <cmath>

/*
    Tingo uses its own Cartesian coordinate system for all transform
    calculations. In our system, (0, 0) is the centre of the screen,
    +X points right, and +Y points up.

    Raylib uses screen coordinates instead: (0, 0) is the top-left
    of the screen, +X points right, and +Y points down.

    Therefore, before rendering, we convert our Cartesian coordinates
    into Raylib's screen coordinates. This conversion happens here,
    at the rendering boundary, so the rest of Tingo's transform system
    can continue to work entirely in Cartesian coordinates.

    DrawTexturePro() also combines the sprite's position and rotation
    around an origin. Its destination position represents where that
    origin is located on screen. Our transform system keeps position
    and pivot as separate concepts, so we calculate the screen-space
    position of our pivot and give that to DrawTexturePro() as its
    destination position.

    The origin must also be converted into Raylib's local coordinate
    system. Raylib measures the origin from the top-left of the
    destination rectangle, whereas our pivot is stored as a Cartesian
    offset from the centre of the sprite. Therefore, we start at the
    centre of the rendered sprite (width / 2, height / 2) and add the
    pivot offset. The Y component is inverted because Cartesian +Y
    points upward while Raylib's local +Y points downward.

    In other words:

        Tingo coordinates
                |
                |  Cartesian -> screen conversion
                v
        screenPosition / pivotScreen
                |
                |  translate our position + pivot into
                |  Raylib's destination + origin system
                v
        DrawTexturePro()
                |
                v
            Rendered sprite

    This keeps Raylib's coordinate/origin requirements contained
    inside this function without changing the meaning of MyTransform.
*/

void DrawTextureCartesian(
    Texture2D texture,
    Rectangle source,
    MyTransform transform
)
{
    Vector2 screenPosition =
    {
        SCREEN_WIDTH / 2.0f + transform.position.x * transform.scale,
        SCREEN_HEIGHT / 2.0f - transform.position.y * transform.scale
    };

    Vector2 pivotScreen =
    {
        screenPosition.x + transform.pivot.x * transform.scale,
        screenPosition.y - transform.pivot.y * transform.scale
    };

    float width = source.width * transform.scale;
    float height = source.height * transform.scale;

    Vector2 origin =
    {
        width / 2.0f + transform.pivot.x * transform.scale,
        height / 2.0f - transform.pivot.y * transform.scale
    };

    Rectangle destination =
    {
        pivotScreen.x,
        pivotScreen.y,
        width,
        height
    };

    DrawTexturePro(
        texture,
        source,
        destination,
        origin,
        -transform.rotation,
        WHITE
    );
}

// Update the sprite's animation.
void Sprite::Update(float dt)
{
    animation.Update(dt);
}

void Sprite::Draw() const
{
    Rectangle source = animation.GetSourceRectangle();

    DrawTextureCartesian(texture, source, transform);
}

// Release the sprite's texture.
void Sprite::Shutdown()
{
    UnloadTexture(texture);
}

void Sprite::SetTransform(MyTransform transform)
{
    this->transform = transform;
}