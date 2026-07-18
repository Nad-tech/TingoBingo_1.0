#include "Robot.h"
#include "raylib.h"
#include "Constants.h"

Robot::Robot()
{
	position = ROBOT_INITIAL_POSITION;
    head.SetPosition(position);
}

void Robot::Update(float dt)
{
    head.Update(dt);
}

void Robot::SetPosition(Vector2 position)
{
    this->position = position;
    head.SetPosition(position);
}

Vector2 Robot::GetPosition() const
{
    return position;
}

Vector2 Robot::GetHeadPosition() const
{
    return head.GetPosition();
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
