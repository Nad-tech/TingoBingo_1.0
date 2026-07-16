#pragma once

#include "raylib.h"
class Object
{
public:

    Object();

    void Update(float dt);
    void Draw() const;
    void Initialise();
    void Shutdown();

private:
    Vector2 position;
};