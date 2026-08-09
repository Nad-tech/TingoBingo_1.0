#pragma once

#include "SpeechController.h"
#include <string>

class Robot;

class RobotBrain
{
    public:
        enum class State
        {
            Idle,
            Speaking
        };

        RobotBrain(Robot& robot);

        void Update(float dt);
        void SetState(State newState);
        void Speak(const std::string& command);

    private:
        Robot& robot;
        State state;
        SpeechController speechController;
        bool speaking = false;
};