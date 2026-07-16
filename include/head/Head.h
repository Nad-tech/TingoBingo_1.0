#pragma once

#include "../SpritePart.h"
#include "raylib.h"
#include "Antenna.h"
#include "Ears.h"
#include "Eyebrows.h"
#include "Mouth.h"
#include "Eyes.h"

class Head
{
    public:
        Head();
        
        void Initialise();
        void Shutdown();

        void Update(float dt);
        void Draw() const;

        void SetPosition(Vector2 position);

    private:
       Vector2 position;
    
        SpritePart headBase;
        Eyes eyes;
        Antenna antenna;
        Ears ears;
        Eyebrows eyeBrows;
        Mouth mouth;
};