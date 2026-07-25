#include "Robot.h"
#include "raylib.h"
#include "Constants.h"

Robot::Robot() 
    : idle(head)
{
	position = 
    {
        SCREEN_WIDTH / 2, 
        SCREEN_HEIGHT / 2
    };
}

void Robot::Update(float dt)
{
    head.Update(dt);
    idle.Update(dt);
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

void Robot::LookAt(Vector2 point)
{
    head.LookAt(point);
}