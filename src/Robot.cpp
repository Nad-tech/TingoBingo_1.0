#include "Robot.h"
#include "raylib.h"
#include "Constants.h"

Robot::Robot()
{
	position = {0,0};
    head.SetPosition(position);
}

void Robot::Update(float dt)
{
    head.Update(dt);
}

void Robot::Draw() const
{
	head.Draw();
}

void Robot::Initialise()
{
    head.Initialise();
}

void Robot::Shutdown()
{
    head.Shutdown();
}
