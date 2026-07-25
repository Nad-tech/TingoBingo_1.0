#pragma once
#include "head\Head.h"

class IdleController 
{
    public:
        IdleController(Head& h);
        
        void Update(float dt);
        void UpdateAntenna(float dt);
        void UpdateEars(float dt);
        void UpdateEyebrows(float dt);
        void UpdateEyes(float dt);
        void UpdateMouth(float dt);
        void UpdateNose(float dt);
    
    private:
	    Head& head;

        float antennaIdleAnimationTimer;
	    float nextAntennaIdleAnimation;

        float earsIdleAnimationTimer;
        float nextEarsIdleAnimation;

        float eyebrowsIdleAnimationTimer;
        float nextEyebrowsIdleAnimation;

        float eyesIdleAnimationTimer;
        float nextEyesIdleAnimation;

        float mouthIdleAnimationTimer;
        float nextMouthIdleAnimation;

        float noseIdleAnimationTimer;
        float nextNoseIdleAnimation;
};