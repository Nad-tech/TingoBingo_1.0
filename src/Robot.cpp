#include "Robot.h"
#include "raylib.h"
#include "Constants.h"
#include "RobotBrain.h"
#include <string>
#include "Emotion.h"
#include "SfxController.h"

// Initialise the robot's brain 
Robot::Robot() : robotBrain(*this){}

// Initialise the robot's head and place it at the
// robot's starting position.
void Robot::Initialise()
{
    head.Initialise();
    head.SetPosition(position);

    body.Initialise();

    sfxController.Initialise();
}

// Update the robot's behaviour through RobotBrain,
// then update the head using the current speech state
// and emotional state.
void Robot::Update(float dt)
{
    robotBrain.Update(dt);
    head.Update(dt, speaking, robotBrain.GetEmotion());
    body.Update(dt, speaking, robotBrain.GetEmotion());
}


// Pass a speech request to RobotBrain.
// RobotBrain is responsible for handling the speech behaviour.
void Robot::Speak(const std::string& text)
{
    robotBrain.Speak(text);
}


// Set whether the robot is currently speaking.
// The head uses this state to drive facial animations.
void Robot::SetSpeaking(bool state)
{
    speaking = state;
}


// Set the robot's position and move the head to the
// same position.
void Robot::SetPosition(Vector2 position)
{
    this->position = position;
    head.SetPosition(position);
    body.SetPosition(
            {
                position.x + bodyOffset.x,
                position.y + bodyOffset.y
            });
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
    body.Draw();
    head.Draw();
}

// Release the resources owned by the robot's head.
void Robot::Shutdown()
{
    head.Shutdown();
    body.Shutdown();
    sfxController.Shutdown();
}


// Rotate the head one step to the left.
void Robot::RotateHeadLeft()
{
    head.RotateLeft();
}


// Rotate the head one step to the right.
void Robot::RotateHeadRight()
{
    head.RotateRight();
    body.RotateRight();
}


// Return the head to its forward-facing position.
void Robot::ReturnHeadToCentre()
{
    head.ReturnToCentre();
    body.ReturnToCentre();
}


// Make the robot look towards a specific point.
void Robot::LookAt(Vector2 point)
{
    head.LookAt(point);
}


// Return a reference to the robot's Head object.
Head& Robot::GetHead()
{
    return head;
}


// Change the robot's emotional state through RobotBrain.
void Robot::SetEmotion(Emotion emotion)
{
    robotBrain.SetEmotion(emotion);
}


// Tell RobotBrain that the robot has picked up an object.
void Robot::OnObjectPickedUp(Object& object)
{
    robotBrain.OnObjectPickedUp(object);
}

// Make the robot return its gaze to the forward position.
void Robot::LookForward()
{
    head.LookForward();
}


// Return the origin point of RobotBrain's search ray.
Vector2 Robot::GetSearchRayOrigin()
{
    return robotBrain.GetSearchRayOrigin();
}


// Return the end point of RobotBrain's search ray.
Vector2 Robot::GetSearchRayEnd()
{
    return robotBrain.GetSearchRayEnd();
}


// Give RobotBrain access to the toys available in the game.
void Robot::SetObjectPointers(std::vector<Object*> toys)
{
    robotBrain.SetObjectPointers(toys);
}

void Robot::PlaySfx(std::string sound)
{
    sfxController.PlaySfx(sound);
}