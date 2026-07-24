#pragma once
#include "head\Head.h"

class IdleController 
{
    public:
        IdleController(Head& h);
        void Update(float dt);
        void UpdateAntenna(float dt);
    
    private:
	    float antennaWiggleTimer;
	    float nextAntennaWiggle;
        Head& head;
};