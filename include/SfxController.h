#pragma once
#include "raylib.h"
#include <string>
class SfxController
{
    public:
        void Initialise();
        void Shutdown();
        void PlaySfx(std::string sound);

    private:
        Sound boing;
};