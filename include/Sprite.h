#pragma once

#include "raylib.h"
#include "Animation.h"
#include "Constants.h"

class Sprite
{
protected:
    Texture2D texture;
    Animation animation;

    Vector2 position = {0,0};
    float rotation = 0.0f;
    float scale = 1.0f;
    Vector2 origin = {0,0};

public:
    virtual void Initialise() = 0;

    virtual void Update(float dt);
    virtual void Draw() const;

    void Shutdown();
    
    void SetPosition(Vector2 position);
    Vector2 GetPosition() const;

    void SetRotation(float rotation);

    virtual ~Sprite() = default;
};