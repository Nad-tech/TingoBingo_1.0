#pragma once

#include "Shoulder.h"
#include "BodyDimensions.h"
#include "MyTransform.h"

class Arms
{
    public:
        Arms(BodyDimensions& dimensions);

        void Initialise();
        void Shutdown();

        void Update(float dt);
        void Draw() const;
        
        void SetTransform(MyTransform parentTransform);
        
        void SwingArm(std::string side, bool swing);
        
    private:
        BodyDimensions& dimensions;

        Shoulder leftShoulder;
        Shoulder rightShoulder;

        bool swingLeftArm = false;
        bool swingRightArm = false;
};


