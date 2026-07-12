#include "Object.h"
#include "raylib.h"

Object::Object()
{
    position = {20, 20};
}

void Object::Update(float dt)
{
    position.y += 100 * dt;
}

void Object::Draw() const
{
    DrawCircle(position.x, position.y, 10,RED);
}