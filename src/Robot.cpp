//====================================================
// Robot.cpp
//
// Represents the TingoBingo robot.
//
// The Robot class owns the robot's head and idle
// controller, providing a simple interface for
// updating, drawing and controlling the robot.
//====================================================

#include "Robot.h"
#include "raylib.h"
#include "Constants.h"

// Create the robot and initialise its starting position.
Robot::Robot()
    : idle(head)
{
    position =
    {
        SCREEN_WIDTH / 2,
        SCREEN_HEIGHT / 2
    };
}

// Update the robot and its idle behaviour.
void Robot::Update(float dt)
{
    head.Update(dt);
    idle.Update(dt);
}

// Move the robot to a new position.
void Robot::SetPosition(Vector2 position)
{
    this->position = position;
    head.SetPosition(position);
}

// Return the robot's current position.
Vector2 Robot::GetPosition() const
{
    return position;
}

// Return the current position of the robot's head.
Vector2 Robot::GetHeadPosition() const
{
    return head.GetPosition();
}

// Draw the robot.
void Robot::Draw() const
{
    head.Draw();
}

// Initialise the robot and its components.
void Robot::Initialise()
{
    head.Initialise();
    head.SetPosition(position);
}

// Release resources used by the robot.
void Robot::Shutdown()
{
    head.Shutdown();
}

// Rotate the head one frame to the left.
void Robot::RotateHeadLeft()
{
    head.RotateLeft();
}

// Rotate the head one frame to the right.
void Robot::RotateHeadRight()
{
    head.RotateRight();
}

// Return the head to its forward-facing position.
void Robot::ReturnHeadToCentre()
{
    head.ReturnToCentre();
}

// Make the robot look towards the given point.
void Robot::LookAt(Vector2 point)
{
    head.LookAt(point);
}