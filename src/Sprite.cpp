//====================================================
// Sprite.cpp
//
// Provides a base class for drawable sprites.
//
// A Sprite stores its texture, position, rotation,
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
        position.x,
        position.y,
        animation.GetFrameWidth() * scale,
        animation.GetFrameHeight() * scale
    };

    // Rotate around the centre of the sprite.
    Vector2 origin =
    {
        destination.width / 2.0f,
        destination.height / 2.0f
    };

    DrawTexturePro(
        texture,
        source,
        destination,
        origin,
        rotation,
        WHITE
    );
}

// Release the sprite's texture.
void Sprite::Shutdown()
{
    UnloadTexture(texture);
}

// Set the sprite's world position.
void Sprite::SetPosition(Vector2 position)
{
    this->position = position;
}

// Return the sprite's current position.
Vector2 Sprite::GetPosition() const
{
    return position;
}

// Move the sprite up by one pixel.
void Sprite::MoveSpriteUp()
{
    this->SetPosition(
    {
        this->GetPosition().x,
        this->GetPosition().y - 1.0f
    });
}

// Move the sprite down by one pixel.
void Sprite::MoveSpriteDown()
{
    this->SetPosition(
    {
        this->GetPosition().x,
        this->GetPosition().y + 1.0f
    });
}

// Set the sprite's rotation in degrees.
void Sprite::SetRotation(float rotation)
{
    this->rotation = rotation;
}