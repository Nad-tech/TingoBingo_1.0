#include "RobotBrain.h"
#include "Robot.h"
#include "Input.h"
#include "SpeechController.h"
#include "IdleController.h"
#include <string>
#include "Emotion.h"

class Robot; //Forward declaration

RobotBrain::RobotBrain(Robot& robot)
    : robot(robot),
      state(State::Idle),
      idleController(robot.GetHead())
{}

void RobotBrain::SetState(State state)
{
    this->state = state;
}

void RobotBrain::SetEmotion(Emotion emotion)
{
    this->emotion = emotion;
}

void RobotBrain::Update(float dt)
{
    idleController.Update(dt);
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

    if(emotion == Emotion::Happy && happyTimer <= 2.0f)
    {
        happyTimer += dt;
        SetEmotion(Emotion::Happy);
    }
    else 
    {
        SetEmotion(Emotion::Neutral);
        happyTimer = 0.0f;
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
