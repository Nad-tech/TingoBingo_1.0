#pragma once

#include "raylib.h"
#include "Sprite.h"

class Toy : public Sprite
{
    public:
        void Initialise();
        void Update(float dt);
        void Dragging();
        void SetPosition(Vector2 newPosition);
        Vector2 GetPosition();

    private:
        Vector2 position;
};