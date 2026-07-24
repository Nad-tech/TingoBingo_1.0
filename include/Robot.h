#pragma once

#include "raylib.h"
#include "head/Head.h"
#include "IdleController.h"

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

	Vector2 GetPosition() const;
	Vector2 GetHeadPosition() const;

private:
	Vector2 position;
	
	Head head;
	IdleController idle;
};