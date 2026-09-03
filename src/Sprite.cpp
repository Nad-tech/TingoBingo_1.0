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

// Update the sprite's animation.
void Sprite::Update(float dt)
{
    animation.Update(dt);
}

// Draw the sprite using its current animation frame.
void Sprite::Draw() const
{
    Rectangle source = animation.GetSourceRectangle();

    Rectangle destination =
    {
        anchorPoint.x,
        anchorPoint.y,
        animation.GetFrameWidth() * scale,
        animation.GetFrameHeight() * scale
    };

    Vector2 drawAnchorOffset = {
        anchorOffset.x * scale,
        anchorOffset.y * scale
    };

    DrawTexturePro(
        texture,
        source,
        destination,
        drawAnchorOffset,
        rotation,
        WHITE
    );
}

// Release the sprite's texture.
void Sprite::Shutdown()
{
    UnloadTexture(texture);
}

// Set the sprite's world-space anchor point.
void Sprite::SetAnchorPoint(Vector2 anchorPoint)
{
    this->anchorPoint = anchorPoint;
}

// Return the sprite's current anchor point.
Vector2 Sprite::GetAnchorPoint() const
{
    return anchorPoint;
}

// Set the sprite's rotation in degrees.
void Sprite::SetRotation(float rotation)
{
    this->rotation = rotation;
}
