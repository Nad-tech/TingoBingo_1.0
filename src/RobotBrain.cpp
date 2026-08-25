#include "RobotBrain.h"
#include "Robot.h"
#include "Input.h"
#include "SpeechController.h"
#include <string>
#include "Emotion.h"
#include <cmath>

class Robot; // Forward declaration


//====================================================
// RobotBrain
//
// Controls Tingo's high-level behaviour.
//
// The brain manages:
// - Robot states (Idle, Searching, Speaking, etc.)
// - Emotions
// - Speech
// - Searching for objects
// - The search ray used to detect objects
//====================================================


RobotBrain::RobotBrain(Robot& robot)
    : robot(robot),
      state(State::Idle),
      emotion(Emotion::Neutral)
{}


//====================================================
// SetState
//
// Changes the robot's current behaviour state.
//====================================================

void RobotBrain::SetState(State state)
{
    this->state = state;
}


//====================================================
// SetEmotion
//
// Changes Tingo's current emotion.
//
// Happy also resets the happy timer so the emotion
// gets its full duration whenever it is triggered.
//====================================================

void RobotBrain::SetEmotion(Emotion newEmotion)
{
    emotion = newEmotion;

    if(newEmotion == Emotion::Happy)
    {
        happyTimer = 0.0f;
    }
}


//====================================================
// Update
//
// Main update function for the brain.
//
// Handles:
// - Speech
// - Emotions
// - Idle behaviour
// - Searching behaviour
//====================================================

void RobotBrain::Update(float dt)
{
    speechController.Update();


    //================================================
    // SPEAKING
    //
    // Speech audio has started playing.
    //================================================

    /*if (state == State::Speaking &&
        speechController.SoundLoaded())
    {
        robot.SetSpeaking(true);
        SetEmotion(Emotion::Happy);
    }*/


    //================================================
    // SPEAKING FINISHED
    //
    // Return to Idle when speech has completely
    // finished playing.
    //================================================

    /*if (state == State::Speaking &&
        !speechController.IsSpeaking())
    {
        SetState(State::Idle);

        robot.SetSpeaking(false);

        SetEmotion(Emotion::Neutral);
    }*/


    //================================================
    // HAPPY EMOTION
    //
    // Happy lasts for two seconds before returning
    // to Neutral.
    //================================================

    if (emotion == Emotion::Happy)
    {
        happyTimer += dt;

        if (happyTimer >= 2.0f)
        {
            SetEmotion(Emotion::Neutral);
        }
    }


    //================================================
    // IDLE
    //
    // Tingo looks forward while idle.
    //
    // After 10 seconds, enter Searching mode.
    //================================================

    if (state == State::Idle)
    {
        robot.LookForward();

        idleTimer += dt;

        if (idleTimer >= 10.0f)
        {
            searchTimer = 0.0f;
            idleTimer = 0.0f;

            state = State::Searching;
        }
    }


    //================================================
    // SEARCHING
    //
    // Tingo continuously rotates a search direction
    // and uses a ray to look for objects.
    //
    // Searching lasts for ten seconds before Tingo
    // returns to Idle.
    //================================================

    if (state == State::Searching)
    {
        searchTimer += dt;

        Search(dt);

        if (searchTimer >= 10.0f)
        {
            idleTimer = 0.0f;
            searchTimer = 0.0f;

            state = State::Idle;
        }
    }
}


//====================================================
// Speak
//
// Starts speech and switches the brain into the
// Speaking state.
//====================================================

void RobotBrain::Speak(const std::string& text)
{
    SetState(State::Speaking);

    speechController.Speak(text);
}


//====================================================
// GetEmotion
//
// Returns Tingo's current emotion.
//====================================================

Emotion RobotBrain::GetEmotion()
{
    return emotion;
}


//====================================================
// ToyPickedUp
//
// Called when a toy is picked up.
//
// Currently handles the ball.
//====================================================

void RobotBrain::ToyPickedUp(Vector2 position, std::string toyName)
{
    if(toyName == "ball")
    {
        SetEmotion(Emotion::Happy);

        Speak("Ha ha ha ha, lets play with the ball");

        robot.LookAt(position);
    }
}


//====================================================
// FoodPickedUp
//
// Called when food is picked up.
//
// Currently handles the banana.
//====================================================

void RobotBrain::FoodPickedUp(Vector2 position, std::string foodName)
{
    if(foodName == "banana")
    {
        SetEmotion(Emotion::Happy);

        Speak("Yummy, yummy banana. Can I eat it please?");

        robot.LookAt(position);
    }
}


//====================================================
// Search
//
// Rotates Tingo's search direction continuously.
//
// The search direction is calculated from an angle
// using sine and cosine.
//
// The same direction is used for:
//
// 1. Moving Tingo's pupils.
// 2. Creating the search ray.
//
// The ray currently extends 300 pixels from Tingo's
// head position.
//====================================================

void RobotBrain::Search(float dt)
{
    // Advance the search angle over time.
    searchAngle += searchSpeed * dt;


    // Convert the angle into a unit direction vector.
    //
    // cos = X direction
    // sin = Y direction
    //
    // As the angle increases, the direction rotates
    // around Tingo in a circle.

    Vector2 searchDirection =
    {
        cosf(searchAngle),
        sinf(searchAngle)
    };


    // The ray starts at Tingo's head position.

    searchRayOrigin = robot.GetHeadPosition();


    // Extend the search direction 300 pixels
    // to create the end point of the ray.

    searchRayEnd =
    {
        searchRayOrigin.x + searchDirection.x * 300.0f,
        searchRayOrigin.y + searchDirection.y * 300.0f
    };


    // Make Tingo's pupils look along the search ray.

    robot.LookAt(searchRayEnd);


    // Check whether the search ray has hit any
    // registered toys.

    std::string collidedWithThis =
        DetectCollision(
            searchRayOrigin,
            searchRayEnd
        );


    //================================================
    // BANANA DETECTED
    //================================================

    if(collidedWithThis == "banana")
    {
        SetEmotion(Emotion::Happy);

        Speak("HEY! A banana!");

        robot.LookAt({searchRayEnd});
    }


    //================================================
    // BALL DETECTED
    //================================================

    if(collidedWithThis == "ball")
    {
        SetEmotion(Emotion::Happy);

        Speak("OH! A ball!");

        robot.LookAt({searchRayEnd});
    }
}


//====================================================
// GetSearchRayOrigin
//
// Returns the current start point of the search ray.
//====================================================

Vector2 RobotBrain::GetSearchRayOrigin()
{
    return searchRayOrigin;
}


//====================================================
// GetSearchRayEnd
//
// Returns the current end point of the search ray.
//====================================================

Vector2 RobotBrain::GetSearchRayEnd()
{
    return searchRayEnd;
}


//====================================================
// SetToyPointers
//
// Gives the brain pointers to the toys that it is
// allowed to detect.
//
// The RobotBrain does NOT own these Toys.
// Game still owns them.
//====================================================

void RobotBrain::SetToyPointers(std::vector<Toy*> toys)
{
    this->toys = toys;
}


//====================================================
// DetectCollision
//
// Tests the search ray against every registered Toy.
//
// Each Toy provides a Rectangle collision box.
//
// The ray is tested against:
//
// - The inside of the rectangle
// - Top edge
// - Right edge
// - Bottom edge
// - Left edge
//
// If the ray intersects a Toy, its name is returned.
//
// If nothing is hit, an empty string is returned.
//====================================================

std::string RobotBrain::DetectCollision(
    Vector2 rayOrigin,
    Vector2 rayEnd)
{
    // Check every Toy that the brain knows about.

    for(Toy* toy : toys)
    {
        Rectangle box = toy->GetCollisionBox();


        // Calculate the four corners of the
        // Toy's collision rectangle.

        Vector2 topLeft =
        {
            box.x,
            box.y
        };

        Vector2 topRight =
        {
            box.x + box.width,
            box.y
        };

        Vector2 bottomLeft =
        {
            box.x,
            box.y + box.height
        };

        Vector2 bottomRight =
        {
            box.x + box.width,
            box.y + box.height
        };


        // Check whether the ray intersects the
        // collision rectangle.
        //
        // The first check handles the special case
        // where the ray origin starts inside the box.
        //
        // The remaining four checks test the ray
        // against each edge of the rectangle.

        if
        (
            CheckCollisionPointRec(rayOrigin, box) ||

            CheckCollisionLines(
                rayOrigin,
                rayEnd,
                topLeft,
                topRight,
                nullptr
            ) ||

            CheckCollisionLines(
                rayOrigin,
                rayEnd,
                topRight,
                bottomRight,
                nullptr
            ) ||

            CheckCollisionLines(
                rayOrigin,
                rayEnd,
                bottomRight,
                bottomLeft,
                nullptr
            ) ||

            CheckCollisionLines(
                rayOrigin,
                rayEnd,
                bottomLeft,
                topLeft,
                nullptr
            )
        )
        {
            // Return the name of the Toy that was hit.

            return toy->GetName();
        }
    }


    // Nothing was detected.

    return "";
}