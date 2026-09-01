#pragma once

#include "Sprite.h"
class Arm : public Sprite
{
    public:
    void Initialise() override;
    int GetFrame() const;
    void SetRotation(float rotation);
};