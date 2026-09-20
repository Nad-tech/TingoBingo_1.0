#pragma once

#include "raylib.h"
#include "Body/Head/Antenna.h"
#include "Body/Head/Ears.h"
#include "Body/Head/Eyebrows.h"
#include "Body/Head/Mouth.h"
#include "Body/Head/Eyes.h"
#include "Body/Head/Headbase.h"
#include "Body/Head/Nose.h"
#include "Body/Head/Pupils.h"
#include "Emotion.h"
#include "BodyDimensions.h"
#include "MyTransform.h"

//====================================================
// Head
//
// Controls the complete robot head.
//
// Head owns all of the individual head components and
// keeps them synchronised so they behave as one unit.
//
// Facial features such as the eyes, mouth, eyebrows
// and pupils can animate independently while the
// Headbase handles the main head orientation.
//====================================================

class Head
{
public:
    Head(BodyDimensions& dimensions);
    
    void Initialise();
    void Shutdown();

    void Update(float dt, bool speaking, Emotion emotion);
    void Draw() const;

    void SetTransform(MyTransform parentTransform);

    void LookAt(Vector2 point);

    void LookForward();
    
private:
    BodyDimensions& dimensions;
    MyTransform transform;
    Vector2 positionOffset;

    Headbase headBase;
    Eyes eyes;
    Antenna antenna;
    Ears ears;
    Eyebrows eyebrows;
    Mouth mouth;
    Nose nose;
    Pupils pupils;
};