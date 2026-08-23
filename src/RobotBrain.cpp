#include "RobotBrain.h"
#include "Robot.h"
#include "Input.h"
#include "SpeechController.h"
#include <string>
#include "Emotion.h"
#include <cmath>

class Robot; //Forward declaration

RobotBrain::RobotBrain(Robot& robot)
    : robot(robot),
      state(State::Idle)
{}

void RobotBrain::SetState(State state)
{
    this->state = state;
}

void RobotBrain::SetEmotion(Emotion newEmotion)
{
    emotion = newEmotion;

    if(newEmotion == Emotion::Happy)
    {
        happyTimer = 0.0f;
    }
}

void RobotBrain::Update(float dt)
{
    speechController.Update();

    // Speech audio has started playing.
    if (state == State::Speaking &&
        speechController.SoundLoaded())
    {
        robot.SetSpeaking(true);
        SetEmotion(Emotion::Happy);
    }

    // Speech has completely finished.
    if (state == State::Speaking &&
        !speechController.IsSpeaking())
    {
        SetState(State::Idle);
        robot.SetSpeaking(false);
        SetEmotion(Emotion::Neutral);
    }

    // Happy emotion lasts for 2 seconds.
    if (emotion == Emotion::Happy)
    {
        happyTimer += dt;

        if (happyTimer >= 2.0f)
        {
            SetEmotion(Emotion::Neutral);
        }
    }

    if (state == State::Idle)
    {
        robot.LookForward();

        idleTimer += dt;

        if (idleTimer >= 1.0f)
        {
            searchTimer = 0.0f;
            idleTimer = 0.0f;
            state = State::Searching;
        }
    }

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

void RobotBrain::Speak(const std::string& text)
{
    SetState(State::Speaking);
    speechController.Speak(text);
}

Emotion RobotBrain::GetEmotion()
{
    return emotion;
}

void RobotBrain::ToyPickedUp(Vector2 position, std::string toyName)
{
    if(toyName == "ball")
    {
        SetEmotion(Emotion::Happy);
        Speak("Ha ha ha ha, lets play with the ball");
        robot.LookAt(position);
    }
}

void RobotBrain::FoodPickedUp(Vector2 position, std::string foodName)
{
    if(foodName == "banana")
    {
        SetEmotion(Emotion::Happy);
        Speak("Yummy, yummy banana. Can I eat it please?");
        robot.LookAt(position);
    }

}

void RobotBrain::Search(float dt)
{
    searchAngle += searchSpeed * dt;

    Vector2 searchDirection = 
    {
        cosf(searchAngle),
        sinf(searchAngle)
    };

    searchRayOrigin = robot.GetHeadPosition();

    searchRayEnd =
    {
        searchRayOrigin.x + searchDirection.x * 300.0f,
        searchRayOrigin.y + searchDirection.y * 300.0f
    };

    robot.LookAt(searchRayEnd);

    std::string collidedWithThis = DetectCollision
                                    (
                                        searchRayOrigin,
                                        searchRayEnd
                                    );

    if(collidedWithThis == "banana")
    {
        SetEmotion(Emotion::Happy);
        Speak("HEY! A banana!");
        robot.LookAt({searchRayEnd});
    }

    if(collidedWithThis == "ball")
    {
        SetEmotion(Emotion::Happy);
        Speak("OH! A ball!");
        robot.LookAt({searchRayEnd});
    }
}

Vector2 RobotBrain::GetSearchRayOrigin()
{
    return searchRayOrigin;
}

Vector2 RobotBrain::GetSearchRayEnd()
{
    return searchRayEnd;
}

void RobotBrain::SetToyPointers(std::vector<Toy*> toys)
{
    this->toys = toys;
}

std::string RobotBrain::DetectCollision(Vector2 rayOrigin, Vector2 rayEnd)
{
    for(Toy* toy : toys)
    {
        Rectangle box = toy->GetCollisionBox();

        Vector2 topLeft     = { box.x, box.y };
        Vector2 topRight    = { box.x + box.width, box.y };
        Vector2 bottomLeft  = { box.x, box.y + box.height };
        Vector2 bottomRight = { box.x + box.width, box.y + box.height };

        if
        (   
            CheckCollisionPointRec(rayOrigin, box) ||
            CheckCollisionLines(rayOrigin, rayEnd, topLeft, topRight, nullptr) ||
            CheckCollisionLines(rayOrigin, rayEnd, topRight, bottomRight, nullptr) ||
            CheckCollisionLines(rayOrigin, rayEnd, bottomRight, bottomLeft, nullptr) ||
            CheckCollisionLines(rayOrigin, rayEnd, bottomLeft, topLeft, nullptr)
        )        
        {
            return toy->GetName();
        }
    }
    return "";
}
