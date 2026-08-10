#include "Robot.h"
#include "raylib.h"
#include "Constants.h"
#include "RobotBrain.h"
#include <string>

Robot::Robot() : robotBrain(*this)
{
	position = 
    {
        SCREEN_WIDTH / 2, 
        SCREEN_HEIGHT / 2
    };
}

void Robot::Update(float dt)
{
    robotBrain.Update(dt);
    head.Update(dt, speaking);
}

void Robot::Speak(const std::string& text)
{
    robotBrain.Speak(text);
}

void Robot::SetSpeaking(bool state)
{
    speaking = state;
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

Head& Robot::GetHead()
{
    return head;
}