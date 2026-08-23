#pragma once

#include "SpeechController.h"
#include <string>
#include "Emotion.h"
#include <vector>
#include "Toy.h"
#include <string>

class Robot;

class RobotBrain
{
    public:
        enum class State
        {
            Idle,
            Speaking,
            Searching
        };

        RobotBrain(Robot& robot);

        void Update(float dt);

        void SetState(State newState);
        
        void Speak(const std::string& command);
        
        void SetEmotion(Emotion newEmotion);
        Emotion GetEmotion();
        
        void ToyPickedUp(Vector2 position, std::string toyName);
        void FoodPickedUp(Vector2 position, std::string foodName);
        
        void Search(float dt);
        Vector2 GetSearchRayOrigin();
        Vector2 GetSearchRayEnd();

        void SetToyPointers(std::vector<Toy*> toys);

        std::string DetectCollision
                        (
                            Vector2 rayOrigin, 
                            Vector2 rayEnd
                        ); 

    private:
        Robot& robot;
        State state;
        SpeechController speechController;
        bool speaking = false;
        float happyTimer = 0.0f;
        Emotion emotion;
        float searchTimer = 0;
        float idleTimer = 0;
        float searchAngle = 0.0f;
        float searchSpeed = 1.0f;
        Vector2 searchRayOrigin = {};
        Vector2 searchRayEnd = {};
        std::vector<Toy*> toys;
};