#pragma once

#include "SpeechController.h"
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
            Interacting
        };

        RobotBrain(Robot& robot);

        void Update(float dt);

        void SetState(State newState);
        
        void Speak(const std::string& command);
        
        void SetEmotion(Emotion newEmotion);
        Emotion GetEmotion();
        
        void ToyPickedUp(Vector2 position, std::string toyName);
        void FoodPickedUp(Vector2 position, std::string foodName);

    private:
        Robot& robot;
        State state;
        SpeechController speechController;
        bool speaking = false;
        float happyTimer = 0.0f;
        Emotion emotion;
};