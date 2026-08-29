#pragma once

#include "raylib.h"
#include "Sprite.h"
#include <string>

class Object : public Sprite
{
    public:
        void Initialise() override;
        void UpdateObject(float dt, Vector2 mousePosition, bool mousePressed);
        bool IsHeldByMouse() const;
        void SetTextureFilename(std::string textureFilename);
        void DrawCollisionBox();
        Rectangle GetCollisionBox();
        void SetName(std::string toyName);
        std::string GetName();

    private:
        bool heldByMouse = false;
        std::string textureFilename;
        Rectangle collisionBox;
        std::string objectName = "notSet";
};