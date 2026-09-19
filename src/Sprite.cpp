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
#include <iostream>

// Update the sprite's animation.
void Sprite::Update(float dt)
{
    animation.Update(dt);
}

//====================================================
// Sprite Positioning
//
// anchorPoint is the world-space reference point and
// initial position for the sprite. It is also the point
// around which the sprite rotates.
//
// anchorOffset defines how far the sprite is offset
// from the anchorPoint.
//
// anchorPoint and anchorOffset work together to define
// the sprite's actual position in world space.
//
//====================================================
// DrawTexturePro()
//
// DrawTexturePro(
//     texture,
//     source,
//     destination,
//     origin,
//     rotation,
//     tint
// );
//
// texture
//     The texture to draw.
//
// source
//     Defines which part of the texture is drawn.
//     Used here to select the current animation frame.
//
// destination
//     Defines where the reference position is and the
//     size of the sprite when it is drawn.
//
// origin
//     Defines how far the sprite is offset from the
//     reference position.
//
// rotation
//     The rotation angle in degrees around the reference
//     position.
//
// tint
//     The colour applied to the sprite. WHITE draws the
//     sprite using its original colours.
//====================================================
//
// The anchorOffset is scaled with the sprite so that
// the offset remains correctly aligned when the sprite
// is drawn at different scales.
//====================================================
void Sprite::Draw() const
{
    // Get the source rectangle for the current animation frame.
    Rectangle source = animation.GetSourceRectangle();

    //Convert cartesion transform.position to screen coords
    float screenX = SCREEN_WIDTH / 2.0f + transform.position.x;
    float screenY = SCREEN_HEIGHT / 2.0f - transform.position.y;

    //convert cartesion pivot coords to screen pivot coords
    float screenPivotX = 
        animation.GetFrameWidth() * transform.scale / 2.0f + 
        transform.pivot.x;

    float screenPivotY = 
        animation.GetFrameHeight() * transform.scale / 2.0f - 
        transform.pivot.y;
    
    Vector2 screenPivot = {screenPivotX, screenPivotY};

    // Define the sprite's world-space position and scaled size.
    Rectangle destination =
    {
        screenX,
        screenY,
        animation.GetFrameWidth() * transform.scale,
        animation.GetFrameHeight() * transform.scale
    };

    // Draw the selected animation frame at the position
    DrawTexturePro(
        texture,
        source,
        destination,
        screenPivot,
        transform.rotation,
        WHITE
    );
}

// Release the sprite's texture.
void Sprite::Shutdown()
{
    UnloadTexture(texture);
}

// Set the sprite's world-space anchor point.
void Sprite::SetPosition(Vector2 position)
{
    this->transform.position = position;
}

// Return the sprite's current anchor point.
Vector2 Sprite::GetPosition() const
{
    return transform.position;
}

// Set the sprite's rotation in degrees.
void Sprite::SetRotation(float rotation)
{
    this->transform.rotation = rotation;
}

void Sprite::SetTransform(MyTransform transform)
{
    this->transform = transform;
}