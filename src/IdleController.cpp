#include "IdleController.h"

IdleController::IdleController(Head& h)
    : head(h),
      antennaWiggleTimer(0.0f),
      nextAntennaWiggle(3.0f)
{
}

void IdleController::Update(float dt)
{
    UpdateAntenna(dt);
}

void IdleController::UpdateAntenna(float dt)
{
    antennaWiggleTimer += dt;
    if(antennaWiggleTimer > nextAntennaWiggle)
    {
        head.WiggleAntenna();
        antennaWiggleTimer = 0.0f;
        nextAntennaWiggle = GetRandomValue(1000,5000) / 1000.0f;
    }
}
