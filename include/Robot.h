#pragma once

#include "raylib.h"
#include "RobotBrain.h"
#include <string>
#include "Emotion.h"
#include "Object.h"
#include "SfxController.h"
#include "body/Body.h"
#include "BodyDimensions.h"
#include "MyTransform.h"

class Robot
{
public:
    Robot();
    void Initialise();
    void Shutdown();
    void Update(float dt);
    void Draw() const;
    void SetTransform(MyTransform transform);
    MyTransform GetTransform();
    void LookAt(Vector2 point);
    //Vector2 GetHeadTransform() const;
    void Speak(const std::string& text);
    void SetSpeaking(bool state);
    void SetEmotion(Emotion emotion);
    void OnObjectPickedUp(Object& object);
    void LookForward();
    Vector2 GetSearchRayOrigin();
    Vector2 GetSearchRayEnd();
    void SetObjectPointers(std::vector<Object*> objects);
    void PlaySfx(std::string sound);
    void SwingArm(std::string side, bool swinging);
    //Vector2 GetHeadWorldPosition();

private:
    BodyDimensions dimensions;
    MyTransform transform;
    Body body;
    RobotBrain robotBrain;
    bool speaking = false;
    SfxController sfxController;
};