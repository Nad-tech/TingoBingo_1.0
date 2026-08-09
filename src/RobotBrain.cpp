#include "RobotBrain.h"
#include "Robot.h"
#include "Input.h"
#include "SpeechController.h"
#include <string>

class Robot; //Forward declaration

RobotBrain::RobotBrain(Robot& robot)
    : robot(robot),
      state(State::Idle)
{}

void RobotBrain::SetState(State state)
{
    this->state = state;
}

void RobotBrain::Update(float dt)
{
    robot.UpdateIdle(dt);

    speechController.Update();

    // Speech audio has started playing.
    if (state == State::Speaking &&
        speechController.SoundLoaded())
    {
        robot.SetSpeaking(true);
    }

    // Speech has completely finished.
    if (state == State::Speaking &&
        !speechController.IsSpeaking())
    {
        SetState(State::Idle);
        robot.SetSpeaking(false);
    }
}

void RobotBrain::Speak(const std::string& text)
{
    SetState(State::Speaking);
    speechController.Speak(text);
}