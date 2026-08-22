#pragma once

#include "raylib.h"
#include "Sprite.h"
#include <string>

class Toy : public Sprite
{
    public:
        void Initialise() override;
        void UpdateToy(float dt, Vector2 mousePosition, bool mousePressed);
        bool IsDragging() const;
        void SetTextureFilename(std::string textureFilename);

    private:
        bool dragging = false;
        std::string textureFilename;
};