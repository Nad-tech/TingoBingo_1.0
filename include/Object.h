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
        // True while this object is attached to the mouse cursor.
        bool heldByMouse = false;

        // Cursor-to-anchor distance captured when dragging starts.
        Vector2 mouseGrabOffset = {0, 0};

        // Top-left offset from the anchor to the visible pixel bounds.
        Vector2 collisionOffset = {0, 0};

        std::string textureFilename;

        // Collision bounds around the non-transparent part of the sprite.
        Rectangle collisionBox;
        std::string objectName = "notSet";

        // Dimensions of one frame in the object's texture.
        int FRAME_WIDTH;
        int FRAME_HEIGHT;

};