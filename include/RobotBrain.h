#pragma once

#include "SpeechController.h"
#include "IdleController.h"
#include <string>
#include "Emotion.h"

class Robot;

class RobotBrain
{
    public:
        enum class State
        {
            Idle,
            Speaking,
        };

        RobotBrain(Robot& robot);

        void Update(float dt);
        void SetState(State newState);
        void Speak(const std::string& command);
        void SetEmotion(Emotion newEmotion);
        Emotion GetEmotion();

    private:
        Robot& robot;
        State state;
        SpeechController speechController;
        IdleController idleController;
        bool speaking = false;
        float happyTimer = 0.0f;
        Emotion emotion;
};