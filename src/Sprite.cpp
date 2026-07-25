#include "Sprite.h"

void Sprite::Update(float dt)
{
    animation.Update(dt);
}

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

void Sprite::Shutdown()
{
    UnloadTexture(texture);
}

void Sprite::SetPosition(Vector2 position)
{
    this->position = position;
}

Vector2 Sprite::GetPosition() const
{
    return position;
}

void Sprite::MoveSpriteUp()
{
    this->SetPosition({this->GetPosition().x, this->GetPosition().y - 1.0f});
}

void Sprite::MoveSpriteDown()
{
    this->SetPosition({this->GetPosition().x, this->GetPosition().y + 1.0f});
}

void Sprite::SetRotation(float rotation)
{
    this->rotation = rotation;
}