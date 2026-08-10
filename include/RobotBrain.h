#pragma once

#include "SpeechController.h"
#include "IdleController.h"
#include "EmotionController.h"
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
        void UpdateIdle(float dt);
        void UpdateEmotion(float dt);

    private:
        Robot& robot;
        State state;
        SpeechController speechController;
        IdleController idleController;
        EmotionController emotionController;
        bool speaking = false;
};