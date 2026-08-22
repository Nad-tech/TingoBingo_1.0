#include "RobotBrain.h"
#include "Robot.h"
#include "Input.h"
#include "SpeechController.h"
#include <string>
#include "Emotion.h"

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