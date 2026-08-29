#pragma once

#include "Robot.h"
#include "Input.h"
#include "Object.h"
class Game
{
public:
	
	void Run();
	
private:
	
	void Initialise();
	void Shutdown();

	void HandleInput();
	void Update(const float dt);
	void Draw();
	
	Robot robot;
	Input input;
	Object ball;
	Object banana;
	Texture2D background;
	std::vector<Object*> objects; 
};