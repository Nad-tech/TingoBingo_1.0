#pragma once

#include "raylib.h"
#include "Animation.h"
#include "Constants.h"
#include "MyTransform.h"

class Sprite
{
protected:
    Texture2D texture;
    Animation animation;
    MyTransform transform;

public:
    virtual void Initialise() = 0;

    virtual void Update(float dt);
    virtual void Draw() const;
    void Shutdown();

    void SetTransform(MyTransform transform);
    
    void SetPosition(Vector2 position);
    Vector2 GetPosition() const;

    void SetRotation(float rotation);
    float GetRotation();

    virtual ~Sprite() = default;
};