#pragma once

#include "Robot.h"
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
	Object object;
};