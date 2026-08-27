#include "RobotBrain.h"
#include "Robot.h"
#include "Input.h"
#include "SpeechController.h"
#include <string>
#include "Emotion.h"
#include <cmath>
#include <iostream>


//====================================================
// Forward declaration
//
// RobotBrain stores a reference to Robot, so Robot
// only needs to be known as a class here.
//====================================================

class Robot;


//====================================================
// RobotBrain
//
// Controls Tingo's high-level behaviour.
//
// The brain manages:
//
// - Robot behaviour states
// - Emotions
// - Speech
// - Idle behaviour
// - Searching for objects
// - The search ray used to detect objects
//
// RobotBrain controls what Tingo is doing, while
// Robot and Head handle the physical and visual
// parts of the robot.
//====================================================


//====================================================
// Constructor
//
// Start Tingo in the Idle state with a Neutral
// emotional state.
//====================================================

RobotBrain::RobotBrain(Robot& robot)
    : robot(robot),
      state(State::Idle),
      emotion(Emotion::Neutral)
{
}


//====================================================
// SetState
//
// Changes Tingo's current high-level behaviour state.
//
// State is used by Update() to determine which
// behaviour should currently run.
//====================================================

void RobotBrain::SetState(State state)
{
    this->state = state;
}


//====================================================
// SetEmotion
//
// Changes Tingo's current emotional state.
//
// When Happy is triggered, the happy timer is reset
// so Tingo gets the full duration of the emotion.
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
// Main update function for RobotBrain.
//
// The SpeechController is updated first so that
// speech generation and audio playback are processed
// before the brain checks the current speech state.
//
// The brain then handles:
//
// - Speech
// - Emotions
// - Idle behaviour
// - Searching behaviour
//====================================================

void RobotBrain::Update(float dt)
{
    // Debug information used to monitor the speech
    // lifecycle while developing the system.
    std::cout << "Brain state: "
              << static_cast<int>(state)
              << " | Sound loaded: "
              << speechController.SoundLoaded()
              << " | Speech finished: "
              << speechController.SpeechFinished()
              << '\n';


    // Update the speech system before checking its state.
    speechController.Update();


    //================================================
    // SPEAKING
    //
    // Once the generated sound has been loaded,
    // tell the Robot that speech is active.
    //
    // SpeechFinished() must be false here because
    // the speech may still be playing.
    //================================================

    if(state == State::Speaking &&
       speechController.SoundLoaded() &&
       !speechController.SpeechFinished())
    {
        robot.SetSpeaking(true);

        SetEmotion(Emotion::Happy);
    }


    //================================================
    // SPEAKING FINISHED
    //
    // Return Tingo to Idle once the SpeechController
    // reports that the complete speech lifecycle has
    // finished.
    //
    // SpeechFinished() is different from simply
    // checking whether sound is playing because speech
    // can be in the Generating state before playback
    // begins.
    //================================================

    if(state == State::Speaking &&
       speechController.SpeechFinished())
    {
        std::cout << "BRAIN DETECTED SPEECH FINISHED\n";

        SetState(State::Idle);

        robot.SetSpeaking(false);

        SetEmotion(Emotion::Neutral);
    }


    //================================================
    // HAPPY EMOTION
    //
    // Happy lasts for two seconds before Tingo
    // returns to the Neutral emotion.
    //================================================

    if(emotion == Emotion::Happy)
    {
        happyTimer += dt;

        if(happyTimer >= 2.0f)
        {
            SetEmotion(Emotion::Neutral);
        }
    }


    //================================================
    // IDLE
    //
    // While idle, Tingo looks forward.
    //
    // After ten seconds of inactivity, Tingo enters
    // Searching mode.
    //================================================

    if(state == State::Idle)
    {
        robot.LookForward();

        idleTimer += dt;

        if(idleTimer >= 10.0f)
        {
            searchTimer = 0.0f;
            idleTimer = 0.0f;

            state = State::Searching;
        }
    }


    //================================================
    // SEARCHING
    //
    // While searching, Tingo continuously rotates
    // its search direction and uses a ray to look
    // for registered objects.
    //
    // Searching lasts for ten seconds before Tingo
    // returns to Idle.
    //================================================

    if(state == State::Searching)
    {
        searchTimer += dt;

        Search(dt);

        if(searchTimer >= 10.0f)
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
// Starts a new speech request and changes the brain
// state to Speaking.
//
// SpeechController handles the actual speech
// generation and playback.
//====================================================

void RobotBrain::Speak(const std::string& text)
{
    // Only start a new speech request when the previous
    // speech has completely finished.
    if(speechController.SpeechFinished())
    {
        // Debug message used to confirm that the brain
        // has received a speech request.
        std::cout << "ROBOT BRAIN SPEAK CALLED\n";


        // Tell the brain that Tingo is now handling speech.
        SetState(State::Speaking);


        // Debug message used to confirm the state change.
        std::cout << "Brain state after SetState: "
                << static_cast<int>(state)
                << '\n';


        // Pass the speech request to the SpeechController.
        speechController.Speak(text);
    }
}


//====================================================
// GetEmotion
//
// Returns Tingo's current emotional state.
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
// Controls Tingo's searching behaviour.
//
// A continuously changing angle is converted into
// a direction vector using sine and cosine.
//
// The same direction is used for:
//
// 1. Moving the pupils.
// 2. Creating the search ray.
//
// This keeps Tingo's gaze and search direction
// synchronised.
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
    // around Tingo.
    Vector2 searchDirection =
    {
        cosf(searchAngle),
        sinf(searchAngle)
    };


    // The ray starts at Tingo's head position.
    searchRayOrigin = robot.GetHeadPosition();


    // Extend the direction 300 pixels from Tingo's
    // head to create the search ray.
    searchRayEnd =
    {
        searchRayOrigin.x + searchDirection.x * 300.0f,
        searchRayOrigin.y + searchDirection.y * 300.0f
    };


    // Make Tingo's pupils look in the same direction
    // as the search ray.
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
// Returns the current starting position of the
// search ray.
//====================================================

Vector2 RobotBrain::GetSearchRayOrigin()
{
    return searchRayOrigin;
}


//====================================================
// GetSearchRayEnd
//
// Returns the current ending position of the
// search ray.
//====================================================

Vector2 RobotBrain::GetSearchRayEnd()
{
    return searchRayEnd;
}


//====================================================
// SetToyPointers
//
// Gives RobotBrain pointers to the toys it is
// allowed to detect.
//
// RobotBrain does not own the Toys.
// Game remains responsible for their lifetime.
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
// The ray is checked against:
//
// - The inside of the collision rectangle
// - Top edge
// - Right edge
// - Bottom edge
// - Left edge
//
// Returns the name of the first Toy hit.
//
// Returns an empty string when nothing is detected.
//====================================================

std::string RobotBrain::DetectCollision(
    Vector2 rayOrigin,
    Vector2 rayEnd)
{
    // Check every toy registered with the brain.
    for(Toy* toy : toys)
    {
        Rectangle box = toy->GetCollisionBox();


        // Calculate the four corners of the
        // collision rectangle.
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


        // Check whether the search ray intersects
        // the collision rectangle.
        //
        // The first check handles the special case
        // where the ray starts inside the rectangle.
        //
        // The remaining checks test the ray against
        // each edge of the rectangle.

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


    // No collision was detected.
    return "";
}