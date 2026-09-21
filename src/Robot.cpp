#include "Robot.h"
#include "raylib.h"
#include "Constants.h"
#include "RobotBrain.h"
#include <string>
#include "Emotion.h"
#include "SfxController.h"

// Initialise the robot's brain 
Robot::Robot() : 
    dimensions(),
    transform(),
    body(dimensions),
    robotBrain(*this, dimensions)
{}

// Initialise the robot's head and place it at the
// robot's starting anchor point.
void Robot::Initialise()
{
    body.Initialise();
    body.SetTransform(transform);   
    sfxController.Initialise();
}

// Update the robot's behaviour through RobotBrain,
// then update the body using the current speech state
// and emotional state.
void Robot::Update(float dt)
{
    robotBrain.Update(dt);
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


// Set the robot's anchor point and move the head to the
// same anchor point.
void Robot::SetTransform(MyTransform transform)
{
    this->transform = transform;
    body.SetTransform(this->transform);
}

// Return the robot's current anchor point.
MyTransform Robot::GetTransform() const
{
    return transform;
}

/*
// Return the current transform of the robot's head.
Vector2 Robot::GetHeadTransform() const
{
    return body.GetHeadTransform();
}*/


// Draw the robot.
void Robot::Draw() const
{
    body.Draw();
    robotBrain.Draw();
}

// Release the resources owned by the robot's head.
void Robot::Shutdown()
{
    body.Shutdown();
    sfxController.Shutdown();
}


// Make the robot look towards a specific point.
void Robot::LookAt(Vector2 point)
{
    body.GetHead().LookAt(point);
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
    body.GetHead().LookForward();
}


// Return the origin point of RobotBrain's search ray.
Vector2 Robot::GetSearchRayOrigin() const
{
    return robotBrain.GetSearchRayOrigin();
}


// Return the end point of RobotBrain's search ray.
Vector2 Robot::GetSearchRayEnd() const
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

void Robot::SwingArm(std::string side, bool swinging)
{
    body.SwingArm(side, swinging);
}

/*Vector2 Robot::GetHeadWorldPosition()
{
    return body.GetHeadWorldPosition();
}*/