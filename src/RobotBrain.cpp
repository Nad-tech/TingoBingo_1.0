#include "RobotBrain.h"
#include "Robot.h"
#include "Input.h"
#include "SpeechController.h"
#include "EmotionController.h"
#include "IdleController.h"
#include <string>

class Robot; //Forward declaration

RobotBrain::RobotBrain(Robot& robot)
    : robot(robot),
      state(State::Idle),
      idleController(robot.GetHead()),
      emotionController(robot.GetHead())
{}

void RobotBrain::SetState(State state)
{
    this->state = state;
}

void RobotBrain::Update(float dt)
{
    idleController.Update(dt);
    emotionController.Update(dt);
    speechController.Update();

    // Speech audio has started playing.
    if (state == State::Speaking &&
        speechController.SoundLoaded())
    {
        robot.SetSpeaking(true);
        emotionController.SetEmotion(Emotion::Happy);
    }

    // Speech has completely finished.
    if (state == State::Speaking &&
        !speechController.IsSpeaking())
    {
        SetState(State::Idle);
        robot.SetSpeaking(false);
        emotionController.SetEmotion(Emotion::Neutral);
    }
}

void RobotBrain::Speak(const std::string& text)
{
    SetState(State::Speaking);
    speechController.Speak(text);
}
