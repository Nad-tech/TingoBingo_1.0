#include "Robot.h"
#include "raylib.h"
#include "Constants.h"

Robot::Robot()
{
	position = 
    {
        (SCREEN_WIDTH - ROBOT_WIDTH * SCALE) / 2, 
        (SCREEN_HEIGHT - ROBOT_HEIGHT * SCALE) / 2
    };
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
    head.SetPosition(position);
}

void Robot::Shutdown()
{
    head.Shutdown();
}

void Robot::RotateHeadLeft()
{
    head.RotateLeft();
}

void Robot::RotateHeadRight()
{
    head.RotateRight();
}

void Robot::ReturnHeadToCentre()
{
    head.ReturnToCentre();
}