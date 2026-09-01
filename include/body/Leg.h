#pragma once

#include "Sprite.h"
class Leg : public Sprite
{
    public:
    void Initialise() override;
    int GetFrame() const;
    void SetRotation(float rotation);
};