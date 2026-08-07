#pragma once

#include "raylib.h"
#include "head/Head.h"
#include "IdleController.h"
#include "RobotBrain.h"
#include "SpeechController.h"
#include <string>
class Robot 
{
public:
	
	Robot();	

	void Update(float dt);
	void Draw() const;
	
	void Initialise();
	void Shutdown();

	void SetPosition(Vector2 position);
	
	void RotateHeadLeft();
	void RotateHeadRight();
	void ReturnHeadToCentre();

	void LookAt(Vector2 point);

	Vector2 GetPosition() const;
	Vector2 GetHeadPosition() const;

	void UpdateIdle(float dt);
	void Speak(const std::string& text);

private:
	Vector2 position;
	
	Head head;
	IdleController idleController;
	RobotBrain robotBrain;
};