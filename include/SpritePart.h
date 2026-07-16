#pragma once

#include "raylib.h"

class SpritePart 
{
    public:

        void Initialise();
        void Shutdown();

        void Update();
        void Draw() const;

        void SetPosition(Vector2 p);
        void SetRotation(float r);
        void SetScale(float s);

    protected:
        Vector2 position;
        float rotation;
        float scale;

    private:
        Texture2D texture;
};