#pragma once

#include "raylib.h"
#include "head/Antenna.h"
#include "head/Ears.h"
#include "head/Eyebrows.h"
#include "head/Mouth.h"
#include "head/Eyes.h"
#include "head/Headbase.h"

class Head
{
    public:
        void Initialise();
        void Shutdown();

        void Update(float dt);
        void Draw() const;

        void SetPosition(Vector2 position);
        Vector2 GetPosition() const;

    private:
        Vector2 position;
    
        Headbase headBase;
        Eyes eyes;
        Antenna antenna;
        Ears ears;
        Eyebrows eyeBrows;
        Mouth mouth;
};