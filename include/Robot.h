#pragma once

#include "raylib.h"
#include "head/Head.h"
#include "RobotBrain.h"
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
	
	void Speak(const std::string& text);
	void SetSpeaking(bool state);

	Head& GetHead();

private:
	Vector2 position;
	
	Head head;
	RobotBrain robotBrain;

	bool speaking = false;
};