#pragma once

#include "raylib.h"

class SpritePart
{
public:
    virtual ~SpritePart() = default;

    virtual void Initialise() {}
    virtual void Update(float dt) {(void)dt;}
    virtual void Draw() const {}
    virtual void Shutdown() {UnloadTexture(texture);}

    void SetPosition(Vector2 p) { position = p; }
    void SetRotation(float r) { rotation = r; }
    void SetScale(float s) { scale = s; }

protected:
    Vector2 position{};
    float rotation = 0.0f;
    float scale = 1.0f;
    Texture2D texture{};
};