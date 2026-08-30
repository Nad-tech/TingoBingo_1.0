#include "SfxController.h"
#include <iostream>

void SfxController::Initialise()
{
    boing = LoadSound("./assets/audio/sfx/boing.mp3");
}

void SfxController::PlaySfx(std::string sound)
{
    if(sound == "boing")
    {
        PlaySound(boing);
    }
}

void SfxController::Shutdown()
{
    UnloadSound(boing);
}