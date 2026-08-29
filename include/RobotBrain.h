#pragma once

#include "SpeechController.h"
#include <string>
#include "Emotion.h"
#include <vector>
#include "Object.h"
#include <string>

class Robot;

class RobotBrain
{
    public:
        enum class State
        {
            Idle,
            Searching,
            Reacting
        };

        RobotBrain(Robot& robot);

        void Update(float dt);

        void SetState(State newState);
        
        void Speak(const std::string& command);
        
        void SetEmotion(Emotion newEmotion);
        Emotion GetEmotion();
        
        void OnObjectPickedUp(Object& object);
        
        void Search(float dt);
        Vector2 GetSearchRayOrigin();
        Vector2 GetSearchRayEnd();

        void SetObjectPointers(std::vector<Object*> objects);

        Object* DetectCollision
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
        std::vector<Object*> objects;
        bool reactionCoolDown = false;
        float reactionCoolDownTimer = 0.0f;
        Object* targetObject;
        Object* detectedObject;
        float detectedTimer = 0.0f;
};