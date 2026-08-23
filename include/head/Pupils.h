#pragma once

#include "head/Pupil.h"
#include "raylib.h"

class Pupils
{
    public:
        void Initialise();
        void Shutdown();
        void Update(float dt);
        void Draw() const;
        void SetPosition(Vector2 position);
        void SetRotation(float rotation);
        Vector2 RotateVector(Vector2 v, float rotation);

        void LookAt(Vector2 point);
        void LookForward();

    private:
        Pupil leftPupil;
        Pupil rightPupil;
};