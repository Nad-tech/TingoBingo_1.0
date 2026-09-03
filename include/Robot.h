#pragma once

#include "raylib.h"
#include "RobotBrain.h"
#include <string>
#include "Emotion.h"
#include "Object.h"
#include "SfxController.h"
#include "body/Body.h"


//====================================================
// Robot
//
// Represents the complete TingoBingo robot.
//
// Robot acts as the interface between the game,
// RobotBrain and Head. RobotBrain controls behaviour
// while Head handles the robot's visual appearance
// and facial animations.
//====================================================

class Robot
{
public:

    // Create the robot and initialise its starting state.
    Robot();


    // Update the robot's behaviour and visual state.
    void Update(float dt);

    // Draw the robot.
    void Draw() const;


    // Load and release the robot's visual resources.
    void Initialise();
    void Shutdown();


    // Set the robot's world-space anchor point.
    void SetAnchorPoint(Vector2 anchorPoint);

    // Make the robot look towards a specific point.
    void LookAt(Vector2 point);


    // Return the robot and head anchor points.
    Vector2 GetAnchorPoint() const;
    Vector2 GetHeadAnchorPoint();


    // Send a speech request to RobotBrain and update
    // the speaking state used by the head's animations.
    void Speak(const std::string& text);
    void SetSpeaking(bool state);


    // Change the robot's emotional state.
    void SetEmotion(Emotion emotion);

    // Notify RobotBrain when the robot interacts with
    // toys or food.
    void OnObjectPickedUp(Object& object);
    
    // Return the robot's gaze to the forward position.
    void LookForward();

    // Return the start and end points of RobotBrain's
    // current search ray.
    Vector2 GetSearchRayOrigin();
    Vector2 GetSearchRayEnd();

    // Give RobotBrain access to the toys currently
    // available in the game.
    void SetObjectPointers(std::vector<Object*> objects);

    void PlaySfx(std::string sound);

private:

    // Current world-space anchor point of the robot.
    Vector2 anchorPoint;

    // Controls the robot's behaviour and state.
    RobotBrain robotBrain;

    // True while the robot is currently speaking.
    // The Head uses this to drive mouth/face animation.
    bool speaking = false;

    SfxController sfxController;

    Body body;
};