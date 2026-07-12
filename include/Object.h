#pragma once

#include "raylib.h"
class Object
{
public:

    Object();

    void Update(float dt);
    void Draw() const;

private:
    Vector2 position;
};