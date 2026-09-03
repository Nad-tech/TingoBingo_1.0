#pragma once

#include "raylib.h"
#include "Animation.h"
#include "Constants.h"

class Sprite
{
protected:
    Texture2D texture;
    Animation animation;

    Vector2 anchorPoint = {0,0};
    float rotation = 0.0f;
    float scale = 1.0f;
    Vector2 anchorOffset = {0,0};

public:
    virtual void Initialise() = 0;

    virtual void Update(float dt);
    virtual void Draw() const;

    void Shutdown();
    
    void SetAnchorPoint(Vector2 anchorPoint);
    Vector2 GetAnchorPoint() const;

    void SetRotation(float rotation);

    virtual ~Sprite() = default;
};