#pragma once

#include "raylib.h"
#include "head/Head.h"

class Robot 
{
public:
	
	Robot();	

	void Update(float dt);
	void Draw() const;
	
	void Initialise();
	void Shutdown();

	void SetPosition(Vector2 position);
	
	Vector2 GetPosition() const;
	Vector2 GetHeadPosition() const;

private:
	Vector2 position;
	
	Head head;
};